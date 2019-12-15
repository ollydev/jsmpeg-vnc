#include <windows.h>
#include <stdio.h>
#include <direct.h>

double os_get_time(void)
{
    LARGE_INTEGER clock_freq, current_time;
	double time_val;

    QueryPerformanceFrequency(&clock_freq);
	QueryPerformanceCounter(&current_time);
	time_val = (double)current_time.QuadPart;
	time_val *= 1000000000.0;
	time_val /= clock_freq.QuadPart;

	return time_val / 1000000;
}

void os_set_clipboard(char *contents) {
    const size_t len = strlen(contents) + 1;
    HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(mem), contents, len);
    GlobalUnlock(mem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, mem);
    CloseClipboard();
}

int os_sleep(int milliseconds) {
    Sleep(milliseconds);
}

void os_save_upload(char *contents, int size, char *filename) {
    _mkdir("uploads");

    FILE *file = fopen(filename, "w+");
    fwrite(contents, sizeof(char), size, file);
    fclose(file);

    printf("\nFile uploaded: %s\n", filename);
}