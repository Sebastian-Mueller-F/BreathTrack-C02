# Projekt: BreathTrack CO2

## Anforderungen

1. **Gegebener Sensor**:

   - **Anforderung**: Ein Sensor, der den CO2-Gehalt der Atemluft misst, ist gegeben. Der Wertebereich liegt zwischen 0 und 100.
   - **Anforderung**: Der Wert soll einmal pro Sekunde aktualisiert werden.
   - **Umsetzung**: Es wurde die Entscheidung getroffen, ein Interface zu entwerfen, welches den Sensor auf einfacher Ebene abstrahiert. Dadurch können sowohl ein Sensorsimulator als auch ein Hardware-Sensor über das Interface einfach in den Rest der Software eingebunden werden.
   - **Interface** (gekürzt):
     ```cpp
     class I_Sensor : public QObject {
       Q_OBJECT
     public:
       explicit I_Sensor(QObject *parent = nullptr) : QObject(parent) {}
       virtual ~I_Sensor() = default;
       virtual void startMeasurement() = 0;
       virtual void stopMeasurement() = 0;
       virtual SensorDataType sensorDataType() const = 0;
     signals:
         void newCo2ValueGenerated(double value, SensorDataType type);
     };
     ```
   - **Details zum Simulator**: Der Simulator erzeugt randomisiert einen Wert basierend auf einem Basiswert und einer Amplitude, die mögliche Ausschläge über den Random-Wert festlegt.

2. **Verteilung des Sensorsignals im System**:

   - **Anforderung**: Der Sensorwert soll im System verteilt werden.
   - **Anforderung**: Die Mittelung soll an die UI und einen Mittelwertbildner propagiert werden.
   - **Umsetzung**: Der Simulator sendet jede Sekunde einen Wert über ein Signal. Unterschiedliche Module im System reagieren auf dieses Signal:
     1. AverageCalculator-Modul
     2. FrontendApi-Modul
     3. In der erweiterten Version: TrendData-Modul

3. **Darstellung in der UI**:

   - **Anforderung**: Die UI soll den gemessenen und den gemittelten Wert darstellen.
   - **Umsetzung**: Das LiveData-Modul des Frontends zeigt auf der linken Seite den gemittelten Wert und auf der rechten Seite den rohen Wert, sowohl als Zahl als auch als visuelle Anzeige.

4. **Einstellbare Mittelungsdauer**:

   - **Anforderung**: Die Dauer der Mittelung soll in 5-Sekunden-Schritten eingestellt werden können.
   - **Umsetzung**: Die Mittelungsdauer kann in den Einstellungen konfiguriert werden. Für die beiden Mittelungsmethoden kann die Dauer unabhängig voneinander festgelegt werden. Dies ist auch notwendig, da in der erweiterten Version mit TrendData beide Mittelwerte im Diagramm angezeigt werden.

5. **Unterschiedliche Mittelwertverfahren**:

   - **Anforderung**: Es sollen zwei unterschiedliche Verfahren zur Mittelwertbildung über die UI einstellbar sein.
   - **Umsetzung**: In der LiveData-Komponente kann der Mittelwertbildner per Klick gewechselt werden.

6. **Build-Anforderungen**:
   - **Anforderung**: Verwenden Sie CMake.
   - **Umsetzung**: CMake wurde für den Build-Prozess verwendet.
   - **Anforderung**: Verwenden Sie C++17 oder höher.
   - **Umsetzung**: C++17 (201703L) wurde verwendet.
   - **Anforderung**: Verwenden Sie Qt 5.15 oder höher.
   - **Umsetzung**: Qt 6.7.2 wurde während der Entwicklung verwendet.
   - **Anforderung**: Das Programm soll unter Linux laufen.
   - **Umsetzung**: Das Programm wurde unter Linux getestet und ausgeführt.
