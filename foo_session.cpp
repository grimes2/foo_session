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
int total_playback_time;
int playback = 1;

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


class play_callback_session : public play_callback_static
{

public:

	virtual unsigned get_flags(void)
	{
		return(flag_on_playback_time);
	}

	virtual void on_playback_time(double p_time)
	{
		total_playback_time++;
		if (total_playback_time == playback * 3600) {
			FB2K_console_formatter() << "Playback " << playback << "h";
			playback++;
		}
	}
	virtual void FB2KAPI on_playback_new_track(metadb_handle_ptr p_track) {}
	virtual void on_playback_stop(play_control::t_stop_reason) {}
	virtual void on_playback_pause(bool) {}
	virtual void on_playback_starting(play_control::t_track_command, bool) {}
	virtual void on_playback_seek(double) {}
	virtual void on_playback_edited(metadb_handle_ptr) {}
	virtual void on_playback_dynamic_info(const file_info&) {}
	virtual void on_playback_dynamic_info_track(const file_info&) {}
	virtual void on_volume_change(float) {}
};

static play_callback_static_factory_t<play_callback_session> g_play_callback_session;