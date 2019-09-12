# **D**ynamic **H**ome **C**omputational **P**robe

Foundation Apprenticeship Year Two Project

## Getting Started

### Dependencies

All dependencies are in [requirements.txt](requirements.txt)

```
numpy==1.12
scipy==0.19.1
scikit-learn==0.18.1
matplotlib
opencv==3.1
jupyter==1.0
notebook>=5.7.2
pandas==0.22
theano
keras==2.1.5
mkl-service==1.1.2
python3-pip
opencv-python==4.1.1.26
hcsr04sensor
cachetools==3.1.1 
futures==3.3.0 
google-api-core==1.14.2 
google-auth==1.6.3 
google-cloud-vision==0.39.0 
googleapis-common-protos==1.6.0 
grpcio==1.23.0 
protobuf==3.9.1 
pyasn1==0.4.7 
pyasn1-modules==0.2.6 
rsa==4.0
rpi-gpio==0.6.5
python3-w1thermsensor
Bluetin-Echo==0.2.0
python3-smbus
```
## Installation

The Raspberry Pi is going to need some initial configuration to run the example code. Also, to support the SMBus2 Python library, we need to install some dependencies.

Firstly, we configure the Rasberry Pi to enable the I2C interface. So, open a Terminal session on the Raspberry Pi to execute the following command:  

```
sudo raspi-config.
```

The Raspberry Pi Configuration Tool will now open to allow you to select interface options. Then on the next screen, 
choose I2C to enable the interface.

![pi-software-configuration-tool](https://github.com/AxiomYT/Dynamic-Home-Computational-Probe/blob/master/pi-software-configuration-tool.png)

Secondly, we now install the dependencies required by the SMBus2 library.
execute the following in the Pi Terminal:

```
sudo apt-get install i2c-tools
```


Lastly, we install SMBus2, which is a drop-in replacement for smbus-cffi/smbus-python in pure Python. Enter the following command in the Terminal:

```
# Either for Python 2.7
pip install smbus2
# Or, for Python 3
pip3 install smbus2
```

## Built With

* [Direwolf](https://github.com/wb2osz/direwolf) - The Packet radio system implemented

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/AxiomYT/Dynamic-Home-Computational-Probe/tags). 

## Authors

* **Logan Tarvit** - *Packet radio system implementation, Sensor platform creation and data transportation across the device, General hardware construction, Webserver Implementation, * - [Axiom](https://github.com/AxiomYT)

* **Rory Cormack** - *AI construction and maintenence, SQL Database construction, High and low level movement processing* - [Liather](https://github.com/Liather)

## License

This project is licensed under the GPL 3.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [W3Schools](https://www.w3schools.com/)
* [Fritzing](https://fritzing.org/home/)
* [Dire Wolf](https://github.com/wb2osz/direwolf)
* [I2C Arduino to Pi](https://github.com/kmaragos/raspi2cino)
