# **D**ynamic **H**ome **C**omputational **P**robe (DHCP)

## Communications branch

“Hams are the people who nearly cause traffic accidents because they are gaping at awesome antennas when they should be paying attention to their driving."

### Packet Radio

* uses our own cursed data protocols - **DNS** ( **D**ata **N**etwork **S**olution )
* Runs over Direwolf
* Station Transciever - Baofeng UV-5R ( 1 W )
* Probe Transicever - Yaesu Vertex VX-150 ( 100mw )

## Getting Started

### Dependencies

All dependencies are in [requirements.txt](requirements.txt)

```
rpi-gpio==0.6.5 X
Bluetin-Echo==0.2.0 X
python3-smbus X
```
## Installation <img src="https://upload.wikimedia.org/wikipedia/en/thumb/9/9f/I%C2%B2C_bus_logo.svg/1200px-I%C2%B2C_bus_logo.svg.png" width="50" height="50" align="right"/>

The Raspberry Pi is going to need some initial configuration to run the code. Also, to support the SMBus2 Python library, we need to install some dependencies.

Firstly, we configure the Rasberry Pi to enable the I2C interface. So, open a Terminal session on the Raspberry Pi to execute the following command:  

```
sudo raspi-config
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
## The Circuit <img src="https://github.com/AxiomYT/Dynamic-Home-Computational-Probe/blob/master/download.png" width="50" height="50" align="right" />



To run the example code, you will need to connect the I2C interface between the Raspberry Pi and Arduino. The Raspberry Pi will have the USB power, while the Arduino has power from the computer USB serial connection. The Arduino is a 3.3v Pro Mini compatible running at 8MHz. And due to the separate power supplies, we need to connect the grounds between the Arduino and Raspberry Pi.

However, this circuit will not be compatible with 5v Arduino board versions. While it is possible to disable the Arduino pull-up resistors, a 5v spike on the I2C is still possible during the pull-up transition.

So, to check the correct installation of the software packages, run the following command at the Terminal Prompt. However, you will need the code uploaded and running on the Arduino. This example code will set the slave address of the Arduino board, and hopefully, this test will detect that address.

```
sudo i2cdetect -y 1
```

![i2cdetect-serial-bus-check](https://github.com/AxiomYT/Dynamic-Home-Computational-Probe/blob/master/i2cdetect-serial-bus-check.png)

## ROS Setup <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRFqAKz_j5ndxEp-YrgNGubPwtNIBkuNkYBLC7JLDk66OUFFYfqYA" width="50" height="50" align="right" />

### Configure your Ubuntu repositories

Configure your Ubuntu repositories to allow "restricted," "universe," and "multiverse." You can follow the Ubuntu guide for instructions on doing this.

### Setup your sources.list

Setup your computer to accept software from packages.ros.org.

```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```

### Set up your keys

```
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```

If you experience issues connecting to the keyserver, you can try substituting hkp://pgp.mit.edu:80 or hkp://keyserver.ubuntu.com:80 in the previous command.

Alternatively, you can use curl instead of the apt-key command, which can be helpful if you are behind a proxy server:

```
curl -sSL 'http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654' | sudo apt-key add -
```

### Installation

First, make sure your Debian package index is up-to-date:
```
sudo apt update
```

There are many different libraries and tools in ROS. We provided four default configurations to get you started. You can also install ROS packages individually.

In case of problems with the next step, you can use following repositories instead of the ones mentioned above ros-shadow-fixed

### Desktop-Full Install: (Recommended) : ROS, rqt, rviz, robot-generic libraries, 2D/3D simulators and 2D/3D perception

sudo apt install ros-melodic-desktop-full
or click here

### Desktop Install: ROS, rqt, rviz, and robot-generic libraries

sudo apt install ros-melodic-desktop
or click here

### ROS-Base: (Bare Bones) ROS package, build, and communication libraries. No GUI tools.
```
sudo apt install ros-melodic-ros-base
```

### Individual Package: You can also install a specific ROS package (replace underscores with dashes of the package name):

```
sudo apt install ros-melodic-PACKAGE
```

e.g.
```
sudo apt install ros-melodic-slam-gmapping
```

To find available packages, use:

```
apt search ros-melodic
```


### Initialize rosdep

Before you can use ROS, you will need to initialize rosdep. rosdep enables you to easily install system dependencies for source you want to compile and is required to run some core components in ROS.

```
sudo rosdep init
rosdep update
```

### Environment setup

It's convenient if the ROS environment variables are automatically added to your bash session every time a new shell is launched:

```
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

If you have more than one ROS distribution installed, ~/.bashrc must only source the setup.bash for the version you are currently using.

If you just want to change the environment of your current shell, instead of the above you can type:

```
source /opt/ros/melodic/setup.bash
```

If you use zsh instead of bash you need to run the following commands to set up your shell:

```
echo "source /opt/ros/melodic/setup.zsh" >> ~/.zshrc
source ~/.zshrc
```

### Dependencies for building packages

Up to now you have installed what you need to run the core ROS packages. To create and manage your own ROS workspaces, there are various tools and requirements that are distributed separately. For example, rosinstall is a frequently used command-line tool that enables you to easily download many source trees for ROS packages with one command.

To install this tool and other dependencies for building ROS packages, run:

```
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
```

## Built With

* [Direwolf](https://github.com/wb2osz/direwolf) - The Packet radio system implemented

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/AxiomYT/Dynamic-Home-Computational-Probe/tags). 

## Authors

* **Logan Tarvit** - *Packet radio system implementation, Sensor platform creation and data transportation across the device, General hardware construction, Webserver Implementation.* - [Axiom](https://github.com/AxiomYT)

* **Rory Cormack** - *AI construction and maintenence, SQL Database construction, High and low level movement processing* - [Liather](https://github.com/Liather)

## License

This project is licensed under the GPL 3.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [BlueTin.IO](https://www.bluetin.io/interfacing/i2c-connect-raspberry-pi-arduino/)
* [W3Schools](https://www.w3schools.com/)
* [Fritzing](https://fritzing.org/home/)
* [Dire Wolf](https://github.com/wb2osz/direwolf)
* [I2C Arduino to Pi](https://github.com/kmaragos/raspi2cino)
* [Communication Standards PDF](http://seniordesignlab.com/wp-content/uploads/2018/03/PIC_MSSP.pdf)
* [I2C Logo \( Philips \(NXP\)) ](https://www.nxp.com/docs/en/data-sheet/PCA9540B.pdf)
* [Circuit SVG](https://www.ohmite.com/)
