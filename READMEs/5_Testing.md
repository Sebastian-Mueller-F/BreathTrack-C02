
# Testing

Leider war es aus zeitlichen Gründen nicht möglich, umfassende Tests für das Projekt umzusetzen. Dennoch wurde ein Grundentwurf erstellt, der zeigt, wie Tests für die wichtigsten Komponenten des Systems, insbesondere für die Sensor- und SMA-Werte sowie die damit verbundenen Signale, implementiert werden könnten.

## Plan für Unit-Tests

Der Plan war, Unit-Tests für folgende Bereiche des Systems zu erstellen:

1. **SensorSimulator**:
   - Testen der korrekten Signalemission durch den SensorSimulator.
   - Sicherstellen, dass die generierten CO2-Werte innerhalb des erwarteten Bereichs liegen.
   - Verifikation, dass die Signale korrekt an andere Systemkomponenten weitergeleitet werden.

2. **SMA- und EMA-Werte**:
   - Testen der korrekten Berechnung der Simple Moving Average (SMA) und Exponential Moving Average (EMA) Werte.
   - Sicherstellen, dass die Mittelwertberechnung in verschiedenen Szenarien (z.B. unterschiedliche Puffergrößen) korrekt funktioniert.
   - Verifikation, dass die berechneten Werte korrekt an die Benutzeroberfläche weitergeleitet und dort dargestellt werden.

3. **Andere wichtige Komponenten**:
   - Tests für die `DataBufferManager`-Klasse, um sicherzustellen, dass die Daten korrekt zwischengespeichert und abgerufen werden.
   - Verifikation der korrekten Interaktion zwischen Backend und Frontend, insbesondere der Kommunikation über Signale und Slots.

## Beispiel für einen Test: SensorSimulator

Ein Beispiel für einen Unit-Test, der die Signalemission des `SensorSimulator` überprüft, könnte folgendermaßen aussehen:

```cpp
#include <QtTest/QtTest>
#include "sensorsimulator.h"

class TestSensorSimulator : public QObject {
    Q_OBJECT
private slots:
    void testSignalEmission() {
        SensorSimulator simulator;
        
        // Mock the random data generation to return a known value
        QSignalSpy spy(&simulator, &SensorSimulator::newCo2ValueGenerated);

        // Replace or intercept the method that generates random values
        simulator.setMockValue(500.0); // Beispielsweise könnte eine Methode zum Setzen eines Mock-Wertes hinzugefügt werden

        simulator.simulate(); // Trigger für das Signal

        QCOMPARE(spy.count(), 1); // Sicherstellen, dass das Signal ausgelöst wurde

        // Überprüfen, ob der gesendete Wert dem Mock-Wert entspricht
        QList<QVariant> arguments = spy.takeFirst(); 
        QCOMPARE(arguments.at(0).toDouble(), 500.0); // Überprüfen, ob der gesendete Wert wie erwartet ist
    }
};

QTEST_MAIN(TestSensorSimulator)
#include "test_sensorsimulator.moc"
```

## Beschreibung des Tests

- **Signalemission testen**: Der Test verwendet `QSignalSpy`, um zu überprüfen, ob das `newCo2ValueGenerated`-Signal des `SensorSimulator` korrekt ausgelöst wird.
- **Mocking von Werten**: Um sicherzustellen, dass der Test reproduzierbar ist, wird ein fester Mock-Wert verwendet. Dieser Wert wird gesetzt, bevor die `simulate`-Methode aufgerufen wird, die das Signal auslöst.
- **Verifikation der Signalwerte**: Der Test überprüft, dass der Wert, der vom Signal gesendet wird, mit dem erwarteten Mock-Wert übereinstimmt.

## Fazit

Obwohl die Tests nicht vollständig umgesetzt werden konnten, bietet der Entwurf eine klare Grundlage für die zukünftige Implementierung von Unit-Tests im Projekt. Die Nutzung von QtTest und `QSignalSpy` ermöglicht es, sowohl die Korrektheit der Logik als auch die ordnungsgemäße Funktion der Signalemission zu verifizieren.
