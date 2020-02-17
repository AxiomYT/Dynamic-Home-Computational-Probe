# DHCP Communication Protocol

---

## Goals

1. Choose the patterns of communication and data transmission
	
2. Establish Design Goals
	
3. Choose the message format "Philosophy"
	
4. Design the message structure: Format, Fields, Types of messages, etc.
	
5. Design the communication rules ( Sequences )

*Steps 4 and 5 Go together.*

---

## How to read this document

1. *Asterix' are the author's interjections*

2. Bulleted and numbered lists are in use to convey a point visually.

3. Hash Heirarchy:
	
	1. Title.
	
	2. Sections.
	
	3. Sub-Headings.
	
	4. Small Content Filler Info.
	
	5. Comparisons. ( Advantages - Disadvantages. )
---

## Patterns of Communication

- ( [Client] >=< [Server] ) 
	{ One party initiates the communication, the other responds. }

- Peer-To-Peer 
	{ Any party may initiate the communication. }

- Heirarchal communication 
	{ Many parties, organised in a heirarchy, and communicate only via branches of the tree. }

*For this Project, a Client - Server relationship is most efficient.*

---

## Patterns of Transmissions

- One-To-One
	{ Only two parties involved in communication at a time. }

- Multicast
	{ One or mor eparties may transmit data to multiple parties at a time. }

- Broadcast
	{ One or more parties may transmit data to all parties at the same time. }

*For this Project, a One-To-One relationship is the only applicable pattern.*

---

## Design Goals

### Defining the framework for communication.

- Should the communication be fast?
	*Not really required above 1200bps, which is the fastest one could reliably communicate over AX.25 KISS packet radio.*

- Do we need reliable exchanges? ( Confirmations and such. )
	*Info should be confirmed once and the mean average taken from the last reading.*

- How important is the authentication of parties?
	*The only real wireless attack vector is intercepting between the radio devices - this is not exactly a worry as one would have to decode the message and it's content. one time authentication is needed*

- Is the transferred data confidential? - What degree of authorization is needed?
	*Transferred data is not confidential - no keys or ssalted hashes are communicated over the protocol.*

- How many types of parties are involved? - Can they all communicate to each other?
	*Two endpoints are involved - They have bidirectional communication at half-duplex*

- Are there bandwidth or connection availibility limitations?
	*AX.25 limits bandwidth at 1200 baud, this is slow - but not impossible with an efficient communication model.*

- Do we need to maintain communication channels? - Are connectionless models more suitable?
	*A constant communication channel will not be required - as last known good data will be retained server-side and conveyed to the user, while being informed of this fact.*

- Do we need complex error handling? ( 1 Bit, 2 Bit, Etc. )
	*AX.25, being an RF modulation - should naturally be anticipated to be lossy and difficult to work with, this worry is slightly depreciated as it's used in an office environment, however the risk is still the same, at least a 1 Bit error correction is required.*

---

### A communication protocol should be:

- Simple

- Scalable

- Efficient

- Extensible

---

## Message Formats


### Two Approaches:

1. Text-Oriented Protocols.

2. Protocols using binary messages.

#### Text Oriented

- All messages are readable character strings.

##### Advantages

- Human Readable, easy to understand and monitor.

- Flexible, easy to extend.

- Easy to test

##### Disadvantages

- Human Readable, easy to read by unauthorised persons ( Without Encryption )

- Maybe become Complex, harder to parse in code.

- May make the messages unjustifiably large.

#### Binary Messages

- Messages are blocks of structured binary data.

##### Advantages

- Better way to structure the data.

- Suitable for large or complex data transfers.

- Messages are as small as possible.

##### Disadvantages

- Hard to read, debug or test.

- Need to consider the data representation conventions on hosts and network. ( "Endianness" )

---

## Designing The Message

- A very important aspect in protocol design.

- Influences all the characteristics of the communication: Scalability, Efficiency, Simplicity, Extensibility.

- The design involves two aspects:

	1. Types of messages.
	2. Message Structure.

---

## Types Of Messages

- One message type for each distinct aspect of communication

- Three categories of messages:

	1. Commands.
	2. Data Transfer.
	3. Control.

- Each category may include several message types.

### Command Messages

#### Define the stages of the dialogue between the parties

##### Command Messages

- Address Various communication aspects:
	
	- Communication initiation or ending.

	- Describe the communication stage ( e.g. Authentication, Status Request, Data Transfer. )

	- Status Changes ( e.g. Requests for switching to the data tranfer mode. )

	- Resource Changes ( e.g requests for new communication channels. )

##### Data Transfer

- Messages that carry data over the network are usually sent as responses to specific commands.

	- Data is usually fragmented in multiple messages.

	- Besides the actual data, may describe:

		- The type of binary data format.

		- Clues for the layout of the sctructured data. ( When the structure is flexible / Dynamic. )

		- Data size, offset or sequence information.

		- Type of the data block: Last / Intermediary. 

##### Control Messages

- Control the dialogue between the parties.

	- Address various communication aspects:

		- Co-ordination ( e.g. receipt confirmation, retry requests. )

		- Cancellation or interruption.

		- Availability Checks.

	- Header

---

## Communication Rules

- Along with the messages, this is the other essential part of the protocol.

- Describe the sequences of commands, data and control messages, at each and all the stages in the communication, for all parties in the system.

- Should be clearly and thoroughly specified, through detailed descriptions of each communication scenario. ( For each possible case of peer interaction. )

---

## Documenting The Design

- The protocol specification must be available for all interested parties, as a specific document

- The specification must be:

	- Clear, easy to understand.

	- Comprehensive. ( Complete )

	- Non-ambiguous.

	- Maintainable. ( For versioning and such )

- By only having the specification, partied must be able to thoroughly implement the software components involved in communication.

---

## Specification Content

- Introduction.
	- Purpose of the protocol, domain, environment, prerequisites.

- The Communication Model.
	- Parties involved, relations, roles, general description of the dialogue flow between components, etc.

- Message Description.
	- Syntax and semantics for all types of messages ( Commands, headers, codes, etc. )

- Sequences of commands and replies.
	- The detailed description of the communication rules, including state diagrams, sequence diagrams, and comprehensive explanations for the procedures.
---

## The Final Protocol


### Command Message

*A command message can either be:*
	- SYN from RPI
	- SYNACK from Arduino
	- ACK from RPI.

		- SYN
			- TX
				Prints over serial from RPI:
				- "SYN. RESPOND, ASAP."

		- SYNACK
			- RX
				- Received over serial by Arduino:
				- "SYN. RESPOND, ASAP."
			- TX
				- Prints over serial from Arduino
				- "SYNACK. RESPOND, ASAP."

		- ACK
			- RX
				- Received over serial by RPI
				- "SYNACK. RESPOND, ASAP."
			- TX
				-"Responds over serial from Arduino"
				- "ACK. RESPOND, STOP."

*This is a slightly confounding setup, but in essentiallity - the dataflow goes:*
	
*RPI TX's SYN, Arduino Receives SYN - Responds SYNACK, RPI Receives SYNACK - Responds ACK*

*This Final ACK message is not reciprocated back from the Arduino, both parties have now established and verified communication and data can now begin to be transmitted.*

* Communicated Data:

	- Three sections to data packet.

	- "SYN. RESPOND, ASAP."
		
		- "SYN" - Starts SYNACK chain.
		
		- "RESPOND" - Waiting for response, holds for 5 seconds before time-out.
		
		- "ASAP" - Time can be set for a response, maximum of 15 seconds.
		
		- "." - Indicates that the section is complete, much like a semicolon in CSS, this gives the protocol the ability to determine how many sections of data there are. control packets can only ever contain 3 sections.

		- "," - Indicates that the word previous to it is a component, and the word after is an argument to that component, much like a colon in CSS.


---

# Written By Logan Tarvit.

---

*Looks Better in Sublime Text - As most things do...*

---