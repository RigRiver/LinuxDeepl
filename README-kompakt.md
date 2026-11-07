# LinuxDeepl

LinuxDeepl ist ein DeepL-Übersetzer für Linux mit grafischer Oberfläche und Sprachausgabe.

![LinuxDeepl Icon](de.rig.LinuxDeepl.png)

## Installation mit dem Terminal

flatpak remote-add --if-not-exists --user linuxdeepl https://RigRiver.github.io/LinuxDeepl/linuxdeepl.flatpakrepo
flatpak install --user linuxdeepl de.rig.LinuxDeepl

flatpak install LinuxDeepl.flatpak

Aus dem Quellcode bauen
1. Projektordner anlegen
mkdir -p ~/LinuxDeepl
cd ~/LinuxDeepl

2. Quelldateien herunterladen
git clone https://github.com/RigRiver/LinuxDeepl.git . denn Punkt nicht

3. Bauen mit CMake
mkdir -p build
cd build
cmake ..
cmake --build . -j

4. Starten
./LinuxDeepl

5. Flatpak bauen (optional)
cd ~/LinuxDeepl
flatpak-builder --repo=docs --gpg-sign=DEIN_GPG_KEY --force-clean --disable-rofiles-fuse build-flatpak de.rig.LinuxDeepl.yaml
flatpak build-update-repo --gpg-sign=DEIN_GPG_KEY --prune docs/
flatpak install --user --from docs/linuxdeepl.flatpakrepo

API-Key
https://www.deepl.com/de/developers

Der Key endet auf :fx (Free-Plan).

Sprachausgabe (optional)
Die Flatpak-Version enthält keine Sprachausgabe. Starte LinuxDeepl außerhalb von Flatpak.

bash
sudo dnf install speech-dispatcher speech-dispatcher-utils
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
bash
spd-say -O
Wenn dort piper oder sd_generic steht: weiter mit Schritt 6.

bash
sudo dnf install espeak-ng
spd-conf -u
bash
spd-say -O
Wenn dort espeak-ng steht: weiter mit Schritt 6.

bash
spd-say "Test"
Wenn es spricht: fertig.

bash
which espeak-ng
bash
sudo dnf install espeak-ng
bash
spd-conf -u
spd-say "Test"
bash
systemctl --user restart speech-dispatcher
spd-say "Test"
bash
AudioOutputMethod "alsa"
bash
systemctl --user restart speech-dispatcher
spd-say "Test"
bash
cd ~/Schreibtisch/Programmieren/Apps/LInuxDeepl./LinuxDeepl/build
./LinuxDeepl
Natürliche Stimmen (optional)
https://github.com/Elleo/pied/releases

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

text

---

**Rig, jetzt sind nur die Befehle drin — kein „Was du sehen wirst", keine Erklärungen. Der User kopiert, was im Codeblock steht, und arbeitet die Schritte von oben nach unten ab.** 🐧🔊
