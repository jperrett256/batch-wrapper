#define UNICODE
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define KILOBYTES(x) ((x) * 1024LL)
#define MEGABYTES(x) (KILOBYTES(x) * 1024LL)

#define SCRATCH_BUF_LEN KILOBYTES(24)

#ifndef BAT_FILENAME
#error Expected BAT_FILENAME to be defined (set to a unicode string).
#endif

#define BAT_EXT L".bat"

int wmain(int argc, wchar_t * argv[])
{
	wchar_t * scratch_buf = VirtualAlloc(NULL, SCRATCH_BUF_LEN, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	wchar_t * full_cmd_line = GetCommandLine();

	// skip over argv[0]
	wchar_t * arg_str = full_cmd_line;
	if (*arg_str == L'"')
	{
		arg_str++;
		while (*arg_str)
		{
			// NOTE we assume no escaped quotes within the quotation for argv[0]
			if (*arg_str++ == L'"') break;
		}
	}
	else
	{
		while (*arg_str && *arg_str != L' ' && *arg_str != L'\t') arg_str++;
	}

	wchar_t * cmd_str = L"/c ";

	size_t cmd_str_len = wcslen(cmd_str);
	size_t bat_str_len = wcslen(BAT_FILENAME);
	size_t ext_str_len = wcslen(BAT_EXT);
	size_t arg_str_len = wcslen(arg_str);

	if (SCRATCH_BUF_LEN < cmd_str_len + bat_str_len + ext_str_len + arg_str_len + 1)
	{
		fprintf(stderr, "%ls: size required by command line options exceeded scratch buffery capacity.\n", argv[0]);
		exit(1);
	}

	wcscpy(scratch_buf, cmd_str);
	wcscat(scratch_buf, BAT_FILENAME);
	wcscat(scratch_buf, BAT_EXT);
	wcscat(scratch_buf, arg_str);

#ifdef DEBUG
	printf("GetCommandLine: %ls\n", full_cmd_line);
	printf("GetCommandLine (arguments only): %ls\n", arg_str);
	printf("Arguments to 'cmd.exe': %ls\n", scratch_buf);
	printf("\n");
	fflush(stdout);
#endif

	STARTUPINFO startup_info =
	{
		.cb = sizeof(STARTUPINFO)
	};

	PROCESS_INFORMATION process_info;

	BOOL success = CreateProcess(
		L"C:\\Windows\\System32\\cmd.exe",
		scratch_buf,
		NULL, NULL, FALSE,
		CREATE_UNICODE_ENVIRONMENT,
		NULL, NULL,
		&startup_info, &process_info
	);

	if (!success)
	{
		fprintf(stderr, "%ls: CreateProcess failed with error code %d\n", argv[0], GetLastError());
		exit(1);
	}

	// you get weird behaviour in cmd if you don't explicitly wait
	WaitForSingleObject(process_info.hProcess, INFINITE);

	// no need to close handles, as we are exiting anyway

	return 0;
}
