# Power-Consumption-Forecast

An IoT based system to save energy and money! 

The Android application on the user’s mobile can be used to control the home appliances. In addition, the users receive a daily notification tapping on which opens the app, showing the cumulative electricity bill generated till the current day and the predicted bill for the month. This allows users to be aware of the power consumption and take measures to conserve it, thereby avoiding indiscriminate power usage and also optimize the expenditure on electricity bills.

->Used ESP8266 Wi-Fi SoC that contains TCP/IP stack and a microcontroller. Flashed it with a firmware written in C++, using Arduino IDE. The firmware configures the SoC in STA (station) mode and connects it to the access point (a Wi-Fi router in this case)

->This IoT device was interfaced to the home energy meter. The device reads the pulse outputs from the energy meter and calculates the units (kW-h) based on the number pulses. These consumption data are posted to the web service (used PHP) and stored in the database. 

->An estimator service takes these data and calculates the estimated power consumption and bill towards the end of the current month. This estimation is notified to the users and can be viewed on the users' Android app.

->Another microcontroller was interfaced to the home appliances, and was programmed to be a simple HTTP server which can be used to toggle the appliances on and off as per the request from the Android app.
