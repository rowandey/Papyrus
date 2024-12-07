
<div align="center">
    <img src="https://static.wikia.nocookie.net/sans-nagito/images/1/12/Papyrus.png/revision/latest?cb=20200609055655" alt="AutoGen Logo" width="100">
</div>


<div align="center">

# Papy (Papyrus)

</div>


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

The following will include instructions on how to run the project. At the moment the project is run by building the executable and then running it through your shell.

```bash
# Build the executable and name it main.out
g++ main.cpp -o main.out

# If required
chmod a+x main.out 

# Run the executable
./main.out

===== OR =====
# With my macro
comp main.cpp
```

---
### Future Ideas


---
### Personal Notes

The directory structure that will be used as a reference will be:
```
project_name/
|-- src/
|   |-- main.cpp
|   |-- module1/
|   |   |-- module1.cpp
|   |   |-- module1.h
|   |-- module2/
|   |   |-- module2.cpp
|   |   |-- module2.h
|-- include/
|   |-- project_name/
|   |   |-- module1.h
|   |   |-- module2.h
|-- lib/
|-- tests/
|   |-- unit_tests.cpp
|-- build/
|-- doc/
|-- CMakeLists.txt
|-- README.md
```

- This post fixed a problem I was having with mysqld
	- https://askubuntu.com/questions/615129/systemd-mysql-wont-stop

- Problem with my dev VM running docker-compose not killing containers properly

Command to run build and execution with a test
```
sudo g++ main.cpp apiClient.cpp clock.cpp commandLine.cpp match.cpp matchBuilder.cpp myRandom.cpp payloadBuilder.cpp threadWorks.cpp -std=c++23 && ./a.out --threads 1 --target "http://10.0.0.7" --type GET
```

Alternatively the following now works as well

```
make rebuild
or
make build

cd bin
./papy --threads 4 --target "http://10.0.0.7" --type GET --verbose
```

> **Note:** Buiding with `make rebuild -j$(nproc)` works but is a little inconsistent and sometimes requires two attempts. Time savings of multi-threaded building of the binary is not really worth it and the usual `make rebuild` is fast enough build time wise and more consistent.

#### Test User
Game Name + Tag: bsawatestuser#test

### Todo:

- Auth

- Imma keep it a buck FRFR, openSSL & HTTPS is giving me a bit of C

- SSL GET is working, SSL POST needs testing
	- Best way to test it is most likely getting the PostgreSQL version of M-Track with the updated testing endpoints up on live and running it there.

### Recent Changes:
- Rebuilt the header structure for the application
- Investigated Coroutines
- Implemented test makefile
	- Build works but only if you run the papy exe from within the bin directory right next to the mappign files.
- Payload can be run from anywhere, Mappings are embedded into the built executable

- I WANT TO EMBED THE JSON MAPPING FILES INTO THE EXECUTABLE SO THE THING IS ALMIGHTY PORTABLE

- Added a proper way of swapping between operating modes
	- Get requests primary
	- Flags for specific custom payload contexts
		- League
		- Ocean
	- `./papy --threads 4 --target "http://10.0.0.7" --endpoint "/addMatch"`
		- **Behavior:**  
			- GET Request
			- No payload
	- `./papy --threads 4 --target "http://10.0.0.7" --endpoint "/addMatch" --payload "{FilePath}"`
		- **Behavior:** 
			- POST Request
			- Specified filepath to JSON
				- Contents of file are streamed in, parsed, and used
	- `./papy --threads 4 --target "http://10.0.0.7" --endpoint "/addMatch" --payload lol`
		- **Behavior:** 
			- POST Request
			- Randomized Generated Match using `matchBuilder`
	- `./papy --threads 4 --target "http://10.0.0.7" --endpoint "/addMatch" --payload ocean`
		- **Behavior:** 
			- POST Request
			- Randomized Generated Match using `oceanBuilder`

- Is payloadBuilder doing anything? Remove it if not. Was just testing out stuff
	- Its been archived

- Work on enabling a simplified system of configuring payload
	- Create a sample payload for use to another API
	- Payload option is configured to:
		- Take in a filepath
		- Read in the file contents
		- Return the contents as JSON

### Name Meaning

This section is completely for fun. I named the project based off the latin word papyrus for paper. I figured that paper is what contains much of humanities knowledge and it is also where people go to obtain new knowledge from others. So the link between that and a project that generates a ton of information was not a far leap for me in my mind.
