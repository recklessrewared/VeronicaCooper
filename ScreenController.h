////////////////////////////////////////////////////////////
// Screen Controller
////////////////////////////////////////////////////////////
#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

////////////////////////////////////////////////////////////
// Read the buttons from the keyboard and monitor how
// long each button has been pressed.
//
// NOTE: This object uses the buttons built into the
// LCD Shield
////////////////////////////////////////////////////////////

////////////////////////////////////
// Configuration Symbols
#define BC_NBUTTONS						(5)		// Total number of buttons
#define BC_DEBOUNCE_DELAY 				(10)	// Debounce in ms

#define BC_BUTTON_NONE					(-1)
#define BC_BUTTON_UP					(0)
#define BC_BUTTON_DOWN					(1)
#define BC_BUTTON_LEFT					(2)
#define BC_BUTTON_RIGHT					(3)
#define BC_BUTTON_SELECT				(4)

typedef enum
{
	Button_State_1 = 0,
	Button_State_2,
} Button_StateT;


class CButtonController
{
	protected:
		Button_StateT m_state;
		int m_buttonRead1;
		int m_buttonRead2;
		unsigned long m_debounceTime;

		bool m_maskButtonsUntilClear;

		// This array stores the millis() from when the button was pressed
		unsigned long m_buttons[BC_NBUTTONS];

	public:

	CButtonController();
	virtual ~CButtonController();

	void setup();

	void processFast();
	void processOneSecond() {}

	unsigned long getButton(int _iButtonID);	// Return ms since button pressed - 0 = not pressed
	void maskButtonsUntilClear();

	void nop() {}
};

////////////////////////////////////////////////////////////
// Virtual call for all screen objects
////////////////////////////////////////////////////////////
class CScreen_Base
{
protected:
	int m_id;

public:
	CScreen_Base(int _id)
	{
		m_id = _id;
	}

	virtual ~CScreen_Base() {};

	int getID()
	{
		return m_id;
	}

	virtual void init()
	{
	}

	virtual void processOneSecond()
	{
	}

	virtual void buttonCheck(CButtonController &_buttons)
	{
		_buttons.nop();
	}
};

#define CScreenController_MAX_SCREENS	(10)
class CScreenController
{
	protected:

	CScreen_Base *m_screenList[CScreenController_MAX_SCREENS];
	int m_screenID;		// Currently displayed screen
	CScreen_Base *findScreen();

	CButtonController m_buttonController;

	public:

	CScreenController();
	virtual ~CScreenController();

	void setup();	// Ready hardware and other objects for operation

	void registerScreen(CScreen_Base *_screen);

	void setScreen(int _screen);	// Chagne currently displayed screen

	void processFast();
	void processOneSecond();
};

#endif
