# LinuxDeepl

LinuxDeepl ist ein DeepL-Übersetzer für Linux mit grafischer Oberfläche und Sprachausgabe.

<<<<<<< HEAD
**LinuxDeepl ist ein inoffizieller Client und steht in keiner Verbindung zur DeepL SE.**
=======
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2
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

<<<<<<< HEAD
**Du brauchst nur das Terminal öffnen und kein Vorwissen besitzen. Folge einfach den Schritten von oben nach unten.**

=======
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2
### Über das Flatpak-Repository (empfohlen)

```bash
flatpak remote-add --user linuxdeepl https://RigRiver.github.io/LinuxDeepl/linuxdeepl.flatpakrepo
flatpak install --user linuxdeepl de.rig.LinuxDeepl
<<<<<<< HEAD
Was du sehen wirst: Nach dem ersten Befehl erscheint keine Meldung (das ist normal). Nach dem zweiten Befehl fragt Flatpak, ob du fortfahren möchtest — antworte mit y und drücke Enter. Am Ende steht „Installation abgeschlossen."
=======
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2

Direkt als .flatpak-Datei
Lade die aktuelle LinuxDeepl.flatpak von der Release-Seite herunter und installiere sie:

<<<<<<< HEAD
bash
flatpak install LinuxDeepl.flatpak
Was du sehen wirst: Flatpak fragt, ob du fortfahren möchtest — antworte mit y und drücke Enter.


Aus dem Quellcode bauen:

Falls alte Version vorhanden - deinstallation:
- flatpak uninstall --system de.rig.LinuxDeepl
- rm -rf ~/.cache/gnome-software
- pkill -9 gnome-software
Prüfen, ob kein Eintrag vorhanden ist:
- find /var/lib/flatpak/exports/share/applications -name "*LinuxDeepl*" 2>/dev/null

- cd /home/limac/Schreibtisch/SysDisc/Desktop/ --- zum Beispiwl

A) Projektordner anlegen
mkdir -p ~/LinuxDeepl
cd ~/LinuxDeepl

B) Quelldateien herunterladen
git clone https://github.com/RigRiver/LinuxDeepl.git . mit Punkt am Ende, wichtig !

C) Bauen mit CMake
mkdir -p build
cd build
cmake ..
cmake --build . -j

D) Starten
./LinuxDeepl

E) Flatpak bauen (optional)
cd ~/LinuxDeepl
flatpak-builder --repo=docs --gpg-sign=DEIN_GPG_KEY --force-clean --disable-rofiles-fuse build-flatpak de.rig.LinuxDeepl.yaml
flatpak build-update-repo --gpg-sign=DEIN_GPG_KEY --prune docs/
flatpak install --user --from docs/linuxdeepl.flatpakrepo


=======
flatpak install LinuxDeepl.flatpak
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2

API-Key
LinuxDeepl benötigt einen DeepL-API-Key. Beim ersten Übersetzen wirst du danach gefragt. Einen kostenlosen Developer-Key (1.000.000 Zeichen, einmalig) bekommst du hier:

https://www.deepl.com/de/developers

Wichtig: Der Key endet auf :fx (Free-Plan). Ein Translator-Abo (Web/Desktop) funktioniert hier nicht.

<<<<<<< HEAD
Was du sehen wirst: Beim ersten Klick auf „Übersetzen" öffnet sich ein Fenster, das nach dem Key fragt. Füge den Key ein und klicke OK.

Sprachausgabe
Die Flatpak-Version enthält keine Sprachausgabe. Wenn du die Sprachausgabe nutzen willst, starte LinuxDeepl außerhalb von Flatpak (die lokale Version).

1. Speech Dispatcher installieren (falls nicht vorhanden)
sudo dnf install speech-dispatcher speech-dispatcher-utils

Was du sehen wirst: Das System fragt nach deinem Passwort. Tippe es ein (es wird nicht angezeigt) und drücke Enter. Danach werden Pakete heruntergeladen und installiert. Am Ende steht „Fertig!" oder ähnlich.

2. Speech Dispatcher als dauerhaften Dienst einrichten
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

Was du sehen wirst: Nach dem letzten Befehl erscheint keine Meldung. Das ist normal.

3. Prüfen, ob eine Stimme geladen ist
spd-say -O

Was du sehen wirst: Eine Liste mit dem Namen einer Stimme (z. B. piper oder espeak-ng). Wenn dort nur dummy steht oder die Liste leer ist, fahre mit Schritt 4 fort.

4. Stimme (Engine) installieren
sudo dnf install espeak-ng
spd-conf -u

Was du sehen wirst: Nach spd-conf -u erscheinen ein paar Fragen. Drücke einfach jedes Mal Enter, um die Standardwerte zu übernehmen.

5. Prüfen, ob die Stimme jetzt geladen ist
spd-say -O

Was du sehen wirst: Jetzt sollte dort espeak-ng stehen. Wenn dort immer noch nur dummy steht, fahre mit Schritt 7 fort.

6. Testen
spd-say "Test"

Was du sehen wirst: Du hörst die Stimme „Test" sagen. Wenn nicht, fahre mit Schritt 7 fort.

7. Wenn keine Stimme gefunden wird
which espeak-ng
Was du sehen wirst: Ein Pfad wie /usr/bin/espeak-ng. Wenn nichts kommt, installiere es:

sudo dnf install espeak-ng

Dann:
spd-conf -u
spd-say "Test"

8. Wenn es immer noch nicht spricht
systemctl --user restart speech-dispatcher
spd-say "Test"

Was du sehen wirst: Wenn es immer noch nicht spricht, prüfe die Audio-Ausgabe in ~/.config/speech-dispatcher/speechd.conf und setze:

text
AudioOutputMethod "alsa"

Dann:
systemctl --user restart speech-dispatcher
spd-say "Test"

9. LinuxDeepl lokal starten
cd ~/Schreibtisch/Programmieren/Apps/LInuxDeepl./LinuxDeepl/build
./LinuxDeepl
Was du sehen wirst: Das LinuxDeepl-Fenster öffnet sich. Klicke auf „Aussprechen" — jetzt sollte die Stimme kommen.

### Natürliche Stimmen (optional)

Standardmäßig klingt die Sprachausgabe roboterhaft (espeak-ng). Für natürliche Stimmen kann **Pied** installiert werden — ein kleines Werkzeug, das **Piper** (neuronale Sprachausgabe) einrichtet:
=======
Sprachausgabe
Die Sprachausgabe nutzt die System-Sprachausgabe (Speech Dispatcher). Standardmäßig klingt sie roboterhaft (espeak-ng). Für natürliche Stimmen kann Pied installiert werden — ein kleines Werkzeug, das Piper (neuronale Sprachausgabe) einrichtet:
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2

https://github.com/Elleo/pied/releases

Nach der Installation von Pied und einer Stimme (z. B. „Karlsson" für Deutsch) klingt die Ausgabe deutlich natürlicher.

<<<<<<< HEAD
**Die Sprachausgabe nutzt Piper (https://github.com/rhasspy/piper). Die Stimmen sind unter CC BY 4.0 lizenziert.**
=======
Getestet auf Deutlichkeit
Die Sprachausgabe wurde systematisch auf Verständlichkeit geprüft — besonders bei den Lauten, die in der Praxis Probleme machen:

„ch" (ich-Laut vs. ach-Laut)

„sch"

Wortfolge und Betonung

Die gewählte Stimme (Karlsson) hat sich dabei als deutlich und natürlich erwiesen.

>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2
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

<<<<<<< HEAD
text

---
=======
>>>>>>> e588dee69f97985eded20f33aedc3b43ea9862d2

