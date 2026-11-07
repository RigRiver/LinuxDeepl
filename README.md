# LinuxDeepl

LinuxDeepl ist ein DeepL-Übersetzer für Linux mit grafischer Oberfläche und Sprachausgabe.

**LinuxDeepl ist ein inoffizieller Client und steht in keiner Verbindung zur DeepL SE.**

![LinuxDeepl Icon](de.rig.LinuxDeepl.png)

## Was ist LinuxDeepl?

LinuxDeepl ist ein DeepL-Übersetzer für Linux mit grafischer Oberfläche. Die App nutzt die DeepL-API, um Texte zwischen vielen Sprachen zu übersetzen. Sie läuft als Flatpak auf jedem Linux-System mit Flatpak-Unterstützung und erscheint in der GNOME-Software.

## Funktionen

- Übersetzung zwischen über 30 Sprachen (DeepL-API)
- Automatische Spracherkennung
- Sprachausgabe für Eingabe und Übersetzung (nutzt die System-Sprachausgabe)
- Kontingent-Anzeige (verbleibende Zeichen der aktuellen Periode)
- Sprachen und Texte bleiben beim Neustart erhalten
- API-Key wird einmalig gespeichert
- Flatpak-Installation über eigenes, GPG-signiertes Repository

## Installation

### Über das Flatpak-Repository (empfohlen)

```bash
flatpak remote-add --if-not-exists --user linuxdeepl https://RigRiver.github.io/LinuxDeepl/linuxdeepl.flatpakrepo
flatpak install --user linuxdeepl de.rig.LinuxDeepl
Direkt als .flatpak-Datei
Lade die aktuelle LinuxDeepl.flatpak von der Release-Seite herunter und installiere sie:

bash
flatpak install LinuxDeepl.flatpak
API-Key
LinuxDeepl benötigt einen DeepL-API-Key. Beim ersten Übersetzen wirst du danach gefragt. Einen kostenlosen Developer-Key (1.000.000 Zeichen, einmalig) bekommst du hier:

https://www.deepl.com/de/developers

Wichtig: Der Key endet auf :fx (Free-Plan). Ein Translator-Abo (Web/Desktop) funktioniert hier nicht.

Sprachausgabe
Die Flatpak-Version enthält keine Sprachausgabe. Wenn du die Sprachausgabe nutzen willst, starte LinuxDeepl außerhalb von Flatpak (die lokale Version).

1. Speech Dispatcher installieren (falls nicht vorhanden)
bash
sudo dnf install speech-dispatcher speech-dispatcher-utils
2. Speech Dispatcher als dauerhaften Dienst einrichten
bash
mkdir -p ~/.config/systemd/user
cat > ~/.config/systemd/user/speech-dispatcher.service << 'EOF'
[Unit]
Description=Speech Dispatcher

[Service]
Type=simple
ExecStart=/usr/bin/speech-dispatcher -t 0
Restart=on-failure

[Install]
WantedBy=default.target
EOF
systemctl --user stop speech-dispatcher.socket 2>/dev/null
systemctl --user disable speech-dispatcher.socket 2>/dev/null
systemctl --user daemon-reload
systemctl --user enable --now speech-dispatcher.service
3. Prüfen, ob eine Stimme geladen ist
bash
spd-say -O
Wenn dort piper oder sd_generic steht: weiter mit Schritt 6.

4. Stimme (Engine) installieren
bash
sudo dnf install espeak-ng
spd-conf -u
5. Prüfen, ob die Stimme jetzt geladen ist
bash
spd-say -O
Wenn dort espeak-ng steht: weiter mit Schritt 6.

6. Testen
bash
spd-say "Test"
Wenn es spricht: fertig.

7. Wenn keine Stimme gefunden wird
bash
which espeak-ng
bash
sudo dnf install espeak-ng
bash
spd-conf -u
spd-say "Test"
8. Wenn es immer noch nicht spricht
bash
systemctl --user restart speech-dispatcher
spd-say "Test"
bash
AudioOutputMethod "alsa"
bash
systemctl --user restart speech-dispatcher
spd-say "Test"
9. LinuxDeepl lokal starten
bash
cd ~/Schreibtisch/Programmieren/Apps/LInuxDeepl./LinuxDeepl/build
./LinuxDeepl
Natürliche Stimmen (optional)
Standardmäßig klingt die Sprachausgabe roboterhaft (espeak-ng). Für natürliche Stimmen kann Pied installiert werden — ein kleines Werkzeug, das Piper (neuronale Sprachausgabe) einrichtet:

https://github.com/Elleo/pied/releases

Nach der Installation von Pied und einer Stimme (z. B. „Karlsson" für Deutsch) klingt die Ausgabe deutlich natürlicher.

Die Sprachausgabe nutzt Piper (https://github.com/rhasspy/piper). Die Stimmen sind unter CC BY 4.0 lizenziert.

Technisches
Sprache: C++ / Qt6

GUI: Qt Widgets (mainwindow.ui)

Netzwerk: QNetworkAccessManager (asynchron)

Sprachausgabe: QTextToSpeech (Speech Dispatcher)

Verteilung: Flatpak mit GPG-signiertem Repository auf GitHub Pages

Metadaten: AppStream-Metainfo (valide)

Lizenz
GPL-3.0-or-later

Autor
RigRiver — alias Rig + Deek
