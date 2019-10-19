# Wi-Fi Direct Legacy Connection C++ WRL Demo

This sample is a simple desktop console application that uses WRL to demonstrate the Wi-Fi Direct legacy AP WinRT API from a desktop application.

Developers of desktop applications can use this sample to see how to replace the deprecated WlanHostedNetwork* API's with the new WinRT API's without modifying the application to become a Universal Windows Application. These API's let an application start a Wi-Fi Direct Group Owner (GO) that acts as an Access Point (AP). This allows devices that do not support Wi-Fi Direct to connect to the Windows device running this application and communicate over TCP/UDP. The API's allow the developer to optionally specify an SSID and passphrase, or use randomly generated ones.

The sample is organized up into the following files:

- **WlanHostedNetworkWinRT.cpp/h** : This contains the code that uses the API in the WlanHostedNetworkHelper class. There is also a IWlanHostedNetworkListener interface that can be used by another application to receive notifications from events in the Wi-Fi Direct API. This part may be used as is or modified to fit your application needs.
- **SimpleConsole.cpp/h** : This is a simple console using iostreams to take command line input and start or stop the Wi-Fi Direct legacy AP. It implements the IWlanHostedNetworkListener to handle receiving messages from the API.
- **WiFiDirectLegacyAPDemo.cpp** : Main entry point that starts the simple console.

**Note** This sample requires Windows 10 to execute, as it uses new API's. It also requires a Wi-Fi Card and Driver that supports Wi-Fi Direct.

To obtain information about Windows 10, go to [Windows 10](http://go.microsoft.com/fwlink/?LinkID=532421)

To obtain information about Microsoft Visual Studio 2015 and the tools for developing Windows apps, go to [Visual Studio 2015](http://go.microsoft.com/fwlink/?LinkID=532422)

## Related topics

### Reference

[Wi-Fi Direct WinRT API](https://msdn.microsoft.com/en-us/library/windows.devices.wifidirect.aspx)

[WlanHostedNetwork* API (deprecated in Windows 10)](https://msdn.microsoft.com/en-us/library/windows/desktop/dd815243.aspx)

## System requirements

**Client:** Windows 10 Insider Preview

**Server:** Windows 10 Insider Preview

**Phone:**  Windows 10 Insider Preview

## Build the sample

1. Start Microsoft Visual Studio 2015 and select **File** \> **Open** \> **Project/Solution**.
2. Go to the directory to which you unzipped the sample. Double-click the Visual Studio 2015 Solution (.sln) file. 
3. Press Ctrl+Shift+B, or select **Build** \> **Build Solution**. 
