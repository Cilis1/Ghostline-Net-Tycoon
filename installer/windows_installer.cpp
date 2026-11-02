#define UNICODE
#define _UNICODE
#include <windows.h>
#include <urlmon.h>
#include <shlobj.h>
#include <filesystem>
#include <string>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shell32.lib")

namespace fs = std::filesystem;
static constexpr wchar_t kDownloadUrl[] = L"https://github.com/Cilis1/Ghostline-Net-Tycoon/releases/latest/download/Ghostline-Windows-x64.zip";
static void message(const wchar_t* text, UINT flags = MB_OK | MB_ICONERROR) {
    MessageBoxW(nullptr, text, L"Ghostline Net Tycoon Installer", flags | MB_SETFOREGROUND);
}
static bool runAndWait(const std::wstring& command) {
    STARTUPINFOW si{}; si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    std::wstring cmd = L"powershell.exe -NoProfile -NonInteractive -ExecutionPolicy Bypass -Command \"" + command + L"\"";
    if (!CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) return false;
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD code = 1; GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
    return code == 0;
}
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    PWSTR localAppData = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppData))) {
        message(L"Could not locate your local application data folder."); return 1;
    }
    fs::path installDir = fs::path(localAppData) / L"Programs" / L"Ghostline Net Tycoon";
    CoTaskMemFree(localAppData);
    wchar_t tempPath[MAX_PATH], tempFile[MAX_PATH];
    if (!GetTempPathW(MAX_PATH, tempPath) || !GetTempFileNameW(tempPath, L"gho", 0, tempFile)) {
        message(L"Could not prepare a temporary download location."); return 1;
    }
    fs::path archive = fs::path(tempFile).replace_extension(L".zip");
    DeleteFileW(tempFile);
    HRESULT hr = URLDownloadToFileW(nullptr, kDownloadUrl, archive.c_str(), 0, nullptr);
    if (FAILED(hr)) {
        message(L"Couldn't download the latest Windows game package from GitHub. Check your internet connection and try again.");
        return 1;
    }
    std::error_code ec;
    fs::create_directories(installDir, ec);
    if (ec) { DeleteFileW(archive.c_str()); message(L"Couldn't create the game installation folder."); return 1; }
    const std::wstring expand = L"Expand-Archive -LiteralPath '" + archive.wstring() + L"' -DestinationPath '" + installDir.wstring() + L"' -Force";
    if (!runAndWait(expand)) {
        DeleteFileW(archive.c_str());
        message(L"The game package downloaded, but Windows couldn't unpack it. Please try again."); return 1;
    }
    DeleteFileW(archive.c_str());
    fs::path game = installDir / L"ghostline.exe";
    if (!fs::exists(game)) { message(L"The downloaded package is missing the game executable."); return 1; }
    HINSTANCE launched = ShellExecuteW(nullptr, L"open", game.c_str(), nullptr, installDir.c_str(), SW_SHOWNORMAL);
    if ((INT_PTR)launched <= 32) { message(L"The game was installed, but Windows couldn't start it. You can launch it from the installation folder.", MB_OK | MB_ICONWARNING); return 1; }
    message(L"Ghostline is installed and starting. You can launch it again from LocalAppData\\Programs\\Ghostline Net Tycoon.", MB_OK | MB_ICONINFORMATION);
    return 0;
}
