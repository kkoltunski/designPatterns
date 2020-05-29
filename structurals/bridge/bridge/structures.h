#ifndef STRUCTURES_H
#define STRUCTURES_H

struct workData {
private:
	enum class operatingMode : bool { automatic = false, manual };

public:
	operatingMode operatingMode{ operatingMode::manual };
	inline void changeToAutomatic() {
		operatingMode = operatingMode::automatic;
	}
	inline void changeToManual() {
		operatingMode = operatingMode::manual;
	}
};

struct measurmentData{
private:
	enum class measuring : bool { absolute = false, relative };

public:
	measuring mode{ measuring::absolute };
	inline void changeToAbsolute() {
		mode = measuring::absolute;
	}
	inline void changeToRelative() {
		mode = measuring::relative;
	}
};

class motionData {
public:
	explicit motionData(int _stepsPerResolution) : stepsPerResolution{ _stepsPerResolution }{
	}

	enum class action : char { clockwise = -1, stop = 0, anticlockwise = 1 };

	inline void SetReferencePoint(){
		actualPosition = referencePoint;
	}
	inline bool isRelativeMeasuringOn(){
		return static_cast<bool>(measuring.mode);
	}
	
	const int stepsPerResolution;
	int referencePoint{ 0 };
	int actualPosition{ 0 };
	measurmentData measuring;
	action movement{ action::stop };
};

#endif // STRUCTURES_H
