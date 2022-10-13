#define _WIN32_WINNT _WIN32_WINNT_WIN7
#define WINVER _WIN32_WINNT_WIN7

#include <helpers/foobar2000+atl.h>

static constexpr const char* component_name = "Session";

DECLARE_COMPONENT_VERSION(
	component_name,
	"1.0",
	"grimes\n\n"
	"Build: " __TIME__ ", " __DATE__
);

VALIDATE_COMPONENT_FILENAME("foo_session.dll");

#define ID_TIMER21 1019

UINT_PTR ptr21 = 0;
int session_time;

VOID CALLBACK SessionTimer(
	HWND hwnd,        // handle to window for timer messages
	UINT message,     // WM_TIMER message
	UINT idEvent1,     // timer identifier
	DWORD dwTime)     // current system time
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