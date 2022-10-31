# temperatureController

#**Requirements:**
- Ensure that the temperature in a room is always between a min and max adjustable temperature. 
- When temp is too low, start heating, when temp is too high start cooling.
  
#**How:**
- Create a component in cpp + api's 
- Create needed test-cases using google test (stub, mock,..)
- Code must be build with cmake
  
#**Result:**
- Basic algorithm created.
- System requires an input coming from the user, which is desired set temperature of the environment.
- System reads a temperature sensor and compare its value with desired temperature.
- If desired temperature is higher, cooling starts.
- If desired temperature is lower, heating starts.
- System tries to keep the temperature stabile in between hysteresis region.
- System changes fan speed according to temperature difference.
- Test cases are created.
