
# 4. Frontend

Das Frontend des Projekts „BreathTracker“ wurde basierend auf einem Beispiel aus der Qt Library, bekannt als **EBike-Design**, entwickelt und angepasst. Die ursprüngliche Vorlage wurde modifiziert, um die spezifischen Anforderungen der CO2-Sensorwertanzeige zu erfüllen. Diese Anpassungen betrafen sowohl die visuelle Darstellung als auch die Funktionalität des Frontends.

## a. LiveData-Komponente

- **Funktionalität**: Die **LiveData-Komponente** ist das zentrale Element des Frontends, das die aktuellen Sensorwerte und deren Mittelwerte in Echtzeit anzeigt. Sie kommuniziert mit dem Backend über die **LiveDataAPI**, um die neuesten Sensordaten sowie die gemittelten Werte abzurufen.
- **Nutzung von Qt**: Durch die Nutzung von Qt-Signalen und -Slots wird eine reibungslose und performante Aktualisierung der angezeigten Werte gewährleistet, ohne dass manuelle Eingriffe erforderlich sind.
- **Integration mit Backend**: Die LiveDataAPI ist nahtlos in das Backend integriert und sorgt dafür, dass die Frontend-Komponente stets mit den aktuellsten Daten versorgt wird. Diese Struktur ermöglicht eine klare Trennung der Logik zwischen Datenverarbeitung (Backend) und Datenvisualisierung (Frontend).

## b. TrendData-Komponente

- **Erweiterung der Funktionalität**: Als kreative Erweiterung der ursprünglichen Aufgabenstellung wurde eine **Trend-Anzeige** entwickelt. Diese Komponente zeigt historische Trenddaten über einen festgelegten Zeitraum (z.B. die letzten 10 Minuten) an.
- **Anbindung an TrendDataAPI**: Die TrendData-Komponente ist direkt an die **TrendDataAPI** angebunden. Dies ermöglicht es der Komponente, nahtlos auf die zwischengespeicherten Daten zuzugreifen und diese in der Benutzeroberfläche anzuzeigen.
- **Design und Anpassung**: Das Frontend für die Trend-Anzeige wurde vollständig eigenständig entwickelt und visuell an die LiveData-Komponente angepasst. Dadurch entsteht ein konsistentes Benutzererlebnis, das sowohl aktuelle als auch historische Daten klar und übersichtlich darstellt.
- **Graphische Darstellung**: Der obere Graph der Trend-Anzeige visualisiert die CO2-Sensorwerte in Echtzeit, während die beiden unteren Graphen die berechneten Werte des **Simple Moving Average (SMA)** und des **Exponential Moving Average (EMA)** darstellen. Diese Darstellung ermöglicht es dem Benutzer, Trends und Muster in den CO2-Werten über einen bestimmten Zeitraum zu erkennen.

## c. SettingsDrawer- und SettingsSection-Komponenten

- **Funktionalität**: Das Frontend enthält zudem die **SettingsDrawer**- und **SettingsSection**-Komponenten, die es dem Benutzer ermöglichen, verschiedene Einstellungen vorzunehmen. Diese Komponenten bieten eine intuitive und leicht zugängliche Möglichkeit, Konfigurationen wie z.B. die Dauer der Mittelung oder die Auswahl des Mittelwertverfahrens direkt in der Anwendung anzupassen.
- **Benutzererlebnis**: Die Einstellungen sind in einem Drawer organisiert, der bei Bedarf ein- und ausgeblendet werden kann, um eine übersichtliche und aufgeräumte Benutzeroberfläche zu gewährleisten. Innerhalb des Drawers sind die Einstellungen in Sektionen organisiert, die dem Nutzer eine klare Struktur und einfache Navigation bieten.

# 5. Design

Das Design des Projekts wurde stark von den Anforderungen an eine übersichtliche und benutzerfreundliche Darstellung der CO2-Werte beeinflusst. Hierbei wurde auf bewährte Designprinzipien gesetzt, um sowohl Funktionalität als auch Ästhetik in Einklang zu bringen.

## a. Anpassung des EBike-Designs

- **Grundlage**: Das ursprüngliche **EBike-Design** aus der Qt Library diente als Ausgangspunkt für das Design der Benutzeroberfläche. Dieses Design wurde umfassend modifiziert, um den spezifischen Anforderungen des CO2-Sensor-Projekts gerecht zu werden.
- **Zielsetzung**: Das Ziel war es, eine Benutzeroberfläche zu schaffen, die sowohl intuitiv bedienbar als auch visuell ansprechend ist. Die Anpassungen umfassten sowohl die Farbschemata als auch das Layout der verschiedenen UI-Komponenten.

## b. Einbindung der TrendData-Komponente

- **Visuelle Konsistenz**: Die TrendData-Komponente wurde so gestaltet, dass sie nahtlos in das bestehende Design integriert ist. Dies stellt sicher, dass die Erweiterung des Funktionsumfangs nicht zu einer fragmentierten Benutzererfahrung führt.
- **Grafische Darstellung**: Die grafischen Elemente der Trend-Anzeige wurden so konzipiert, dass sie die Dynamik der Daten (z.B. Anstiege und Abfälle in den CO2-Werten) klar und deutlich vermitteln. Dabei wurden unterschiedliche Farben und Schattierungen verwendet, um die verschiedenen Datentypen (Sensorwerte, SMA, EMA) visuell zu unterscheiden.

## c. Nutzererlebnis und Benutzerfreundlichkeit

- **Benutzerfreundlichkeit**: Das Design wurde darauf optimiert, die Informationen klar und verständlich darzustellen. Die Nutzer können die wichtigsten Informationen auf einen Blick erfassen, ohne dass komplexe Interaktionen erforderlich sind.
- **Reaktionsfähigkeit**: Die Benutzeroberfläche reagiert schnell auf Änderungen der Daten, was durch die Verwendung der Qt-Signale und -Slots gewährleistet wird. Dies sorgt für eine reibungslose und flüssige Benutzererfahrung.
- **Einstellungen**: Die SettingsDrawer- und SettingsSection-Komponenten tragen wesentlich zur Benutzerfreundlichkeit bei, indem sie dem Nutzer die Möglichkeit bieten, Einstellungen schnell und einfach zu ändern, ohne die Hauptansicht verlassen zu müssen.
