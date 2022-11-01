#define _WIN32_WINNT _WIN32_WINNT_WIN7
#define WINVER _WIN32_WINNT_WIN7

#include <foobar2000/SDK/foobar2000.h>

static constexpr const char* component_name = "Session";

DECLARE_COMPONENT_VERSION(
	component_name,
	"1.4",
	"grimes\n\n"
	"Build: " __TIME__ ", " __DATE__
);

VALIDATE_COMPONENT_FILENAME("foo_session.dll");

#define ID_TIMER21 1019

UINT_PTR ptr21 = 0;
int session_time;

VOID CALLBACK SessionTimer(
	HWND,        // handle to window for timer messages
	UINT,     // WM_TIMER message
	UINT,     // timer identifier
	DWORD)     // current system time
{
	session_time++;
	FB2K_console_formatter() << "Session " << session_time << "h";
}

class start : public initquit
{

public:

	virtual void on_init()
	{
		ptr21 = SetTimer(NULL, ID_TIMER21, 1000 * 3600, (TIMERPROC)SessionTimer);
	}
	virtual void on_quit()
	{
		KillTimer(NULL, ptr21);
	}
};

initquit_factory_t<start> g_start;