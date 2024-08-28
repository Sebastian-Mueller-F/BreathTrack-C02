file(REMOVE_RECURSE
  "BreathTracker/qml/ArcItem.qml"
  "BreathTracker/qml/ArcLeft.qml"
  "BreathTracker/qml/ArcRight.qml"
  "BreathTracker/qml/CircleIndicator.qml"
  "BreathTracker/qml/CustomLabel.qml"
  "BreathTracker/qml/DataTrends.qml"
  "BreathTracker/qml/LiveData.qml"
  "BreathTracker/qml/LiveDataBackground.qml"
  "BreathTracker/qml/SettingsDrawer.qml"
  "BreathTracker/qml/SettingsSection.qml"
  "BreathTracker/qml/images/assist.png"
  "BreathTracker/qml/images/calories.png"
  "BreathTracker/qml/images/ema.png"
  "BreathTracker/qml/images/raw.png"
  "BreathTracker/qml/images/sma.png"
  "BreathTracker/qml/images/speed.png"
  "BreathTracker/qml/main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appBreathTracker_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
