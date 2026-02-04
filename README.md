# Rename_It 

**Rename_It** is a lightweight C++ GUI application designed for fast and efficient batch renaming of anime and media files, specifically optimized for **Jellyfin** library standards.

##  Key Features
- **Jellyfin Compatibility:** Automatically formats files to the `Title S01E01` standard.
- **Broad Format Support:** - **Video:** `.mkv`, `.mp4` (can be easly change in code)
  - **Subtitles:** `.srt`, `.ass`
- **Smart Subtitle Tagging:** Easily append custom language codes to subtitle files (e.g., `episode.pl.srt`).

##  How It Works
1. **Subtitles:** If you have subtitle files, you can add a language extension (e.g., `en`, `pl`) in the app.
2. **Directory:** Choose the root directory of your series.
3. **Apply:** Click **"Apply"** to start the process.
4. **Result:** The program will automatically rename video and subtitle files to the `Name - SXXEXX` format.

## ⚠️ Important: Folder Structure
- If video files are in the main folder without a **Season Folder**, they will automatically be assigned to **Season 01 (S01)**.

**Recommended Folder Structure:**
```text
Name/
├── Season 1/
│   ├── Episode 01.mkv
│   └── Episode 02.mkv
├── Season 2/
│   ├── Ep 1.mkv
│   └── Ep 2.mkv
└── Episode_without_folder.mkv  <-- (Will be renamed to S01)
```
##  Installation & Usage

### Windows (Recommended)
1. Go to the **Releases** tab on this GitHub repository.
2. Download the `Rename_It-Windows.zip` archive.
3. Extract it anywhere and run `Rename_It.exe`.
   *Note: No installation is required; all libraries are statically linked.*

### Linux (Arch / Manjaro / EndeavourOS)
!!!To run the application on Linux, you must have the wxWidgets runtime libraries installed.
1.just download the file from **Releases** called `Rename_It-linux_x64`

##  Roadmap & Future Plans
- [ ] **Live Preview Checklist:** A list view allowing users to check/uncheck specific files and see exactly what the new filename will look like before applying changes.
- [ ] **Undo Functionality:** One-click option to revert the last renaming operation and restore original filenames.
- [ ] **Framework Migration:** Planned transition to **Qt** for a more modern UI
- [ ] **macOS Support:** Native `.app` bundle releases.
