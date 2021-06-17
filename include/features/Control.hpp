#ifndef CONTROL_HPP
#define CONTROL_HPP

typedef enum hostgadget {
	LED_WALL, RC_ROBOT
} HostGadget;

class Control {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static bool enableCommands;
	static HostGadget gadget;

	/* functions */
	static void sendCommand (void);
	static void ctrlLedWall (void);
	static void ctrlRCRobot (void);
	static void switchHost (void);
};

#endif
