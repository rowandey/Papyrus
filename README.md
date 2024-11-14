
# Papy

<img src="https://static.wikia.nocookie.net/sans-nagito/images/1/12/Papyrus.png/revision/latest?cb=20200609055655" alt="AutoGen Logo" width="100">

Papy is an open-source framework that builds League of Legends match JSON files that mimic the JSON files produced from the Riot Games `/lol/match/v5/matches/{matchId}` API endpoint. This endpoint when queried with a specified `matchId` as input gives you a massive JSON file(roughly 3500 lines) containing all of the data related to a match.

The purpose of a tool like this is to be able to rapidly generate a large quantity of semi-accurate match data that will be used to test the database of `MTrack` and the application itself.

### Data Entry
The data will be sent to one of the flask endpoints of `MTrack` itself. This will test the application endpoint itself as well as the database.

---
### Language Choice

The language that I will use for this project will be C++. The reasons for this choice include:
- It will generate JSON files much faster than interpreted languages
- More versatile than a few other options incase scope changes (GO, Python)
	- Other options will create this solution easier
- Project based reinforcement

---
### Requirements

Below are a list of requirements of the application, things that must be created to achieve the required functionality.

##### Parameters
- Target address parameter
- Application modifiers that adjust how fast the data is generated and sent
- Record count to make parameter
	- Zero will be set for the program to run until manually exited

##### Functional Requirements
- Write to "Match to DB" endpoint
	- Pass JSON data via endpoint
	- RAW full JSON file
- Data resembles real match JSON
	- Fields make sense
	- item0-6 for example draw from the codes within the item pool
	- `championName` and `championId` fields also pull from valid ID and name pools
- Papy will be a CLI tool
	- Functional builds for MacOS, Linux, and Windows

---
### Getting Started



---
### Future Ideas

