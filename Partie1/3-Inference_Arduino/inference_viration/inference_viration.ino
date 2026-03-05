#include <Arduino_LSM9DS1.h>

// TFLite Micro (Harvard_TinyMLx)
#include <TensorFlowLite.h>
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

// Model array
#include "model_data.h"

// ============================================================
// CONFIG
// ============================================================
static const int kSamplesPerVibration = 100;     // must match SAMPLES_PER_VIBRATION in notebook
static const unsigned long kSamplePeriodMs = 20; // ~50 Hz (adjust if needed)

static const int kNumFeatures = 6;              // rms_a, var_a, ene_a, rms_g, var_g, ene_g
static const int kNumClasses  = 3;              // idle, weak, strong

static const char* CLASS_NAMES[kNumClasses] = {"idle", "weak", "strong"};

// ============================================================
// NORMALIZATION (COPY FROM NOTEBOOK mean/std)
// Order must match features:
// [rms_a, var_a, ene_a, rms_g, var_g, ene_g]
// ============================================================
// TODO: Replace with your real values from mean.npy and std.npy
static const float MEAN[kNumFeatures] = {
  9.8614591e-01f,  // rms_a
  2.0554654e-04f,  // var_a
  9.7283218e+01f,  // ene_a
  3.9442329e+00f,  // rms_g
  6.1837521e+00f,  // var_g
  2.0385940e+03f   // ene_g
};

static const float STD[kNumFeatures] = {
  1.8657649e-02f,  // rms_a
  2.7554404e-04f,  // var_a
  3.7062142e+00f,  // ene_a
  2.1974897e+00f,  // rms_g
  2.0333469e+01f,  // var_g
  3.3605508e+03f   // ene_g
};

// ============================================================
// TFLITE MICRO GLOBALS
// ============================================================
static tflite::MicroErrorReporter micro_error_reporter;
static tflite::ErrorReporter* error_reporter = &micro_error_reporter;

static const tflite::Model* model = nullptr;
static tflite::AllOpsResolver resolver;
static tflite::MicroInterpreter* interpreter = nullptr;

constexpr int kTensorArenaSize = 10 * 1024;  // Dense model is small
static uint8_t tensor_arena[kTensorArenaSize];

static TfLiteTensor* input = nullptr;
static TfLiteTensor* output = nullptr;

// ============================================================
// HELPERS
// ============================================================
static inline float normalize(float x, int i) {
  return (x - MEAN[i]) / (STD[i] + 1e-6f);
}

void setup_tflm() {
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("ERROR: Model schema mismatch!");
    while (1) delay(100);
  }

  static tflite::MicroInterpreter static_interpreter(
    model,
    resolver,
    tensor_arena,
    kTensorArenaSize,
    error_reporter
  );
  interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("ERROR: AllocateTensors() failed");
    Serial.println("Try increasing kTensorArenaSize if needed.");
    while (1) delay(100);
  }

  input = interpreter->input(0);
  output = interpreter->output(0);

  // Expect input shape [1, 6]
  if (input->dims->size != 2 || input->dims->data[0] != 1 || input->dims->data[1] != kNumFeatures) {
    Serial.println("ERROR: Unexpected input tensor shape (expected [1,6])");
    while (1) delay(100);
  }

  Serial.println("TFLM ready ✅");
}

void compute_features_and_predict() {
  // Accumulators
  float sum_a = 0.0f, sum_a2 = 0.0f;
  float sum_g = 0.0f, sum_g2 = 0.0f;

  unsigned long last = millis();

  for (int i = 0; i < kSamplesPerVibration; i++) {
    // Keep a stable sampling rate
    while (millis() - last < kSamplePeriodMs) {}
    last = millis();

    // Wait for IMU data
    while (!(IMU.accelerationAvailable() && IMU.gyroscopeAvailable())) {}

    float ax, ay, az;
    float gx, gy, gz;

    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    float a_mag = sqrtf(ax * ax + ay * ay + az * az);
    float g_mag = sqrtf(gx * gx + gy * gy + gz * gz);

    sum_a += a_mag;
    sum_a2 += a_mag * a_mag;

    sum_g += g_mag;
    sum_g2 += g_mag * g_mag;
  }

  // Features (same as notebook)
  float mean_a = sum_a / kSamplesPerVibration;
  float var_a  = sum_a2 / kSamplesPerVibration - mean_a * mean_a;
  float rms_a  = sqrtf(sum_a2 / kSamplesPerVibration);
  float ene_a  = sum_a2;

  float mean_g = sum_g / kSamplesPerVibration;
  float var_g  = sum_g2 / kSamplesPerVibration - mean_g * mean_g;
  float rms_g  = sqrtf(sum_g2 / kSamplesPerVibration);
  float ene_g  = sum_g2;

  float features[kNumFeatures] = {rms_a, var_a, ene_a, rms_g, var_g, ene_g};

  // Fill input tensor (float model)
  for (int i = 0; i < kNumFeatures; i++) {
    input->data.f[i] = normalize(features[i], i);
  }

  // Inference
  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("ERROR: Invoke failed");
    return;
  }

  // Output is float32 probabilities (softmax)
  int best = 0;
  float best_p = output->data.f[0];
  for (int i = 1; i < kNumClasses; i++) {
    float p = output->data.f[i];
    if (p > best_p) {
      best_p = p;
      best = i;
    }
  }

  Serial.print("Pred: ");
  Serial.print(CLASS_NAMES[best]);
  Serial.print(" | p=");
  Serial.println(best_p, 4);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  if (!IMU.begin()) {
    Serial.println("ERROR: IMU.begin() failed");
    while (1) delay(1000);
  }

  Serial.println("IMU OK ✅");
  setup_tflm();

  Serial.println("Starting real-time vibration classification...");
  Serial.println("Each prediction uses 100 samples (~2 seconds @ 50 Hz).");
}

void loop() {
  compute_features_and_predict();
  // Small pause between predictions (optional)
  delay(200);
}