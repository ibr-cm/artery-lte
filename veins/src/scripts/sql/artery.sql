#
# Create tables for ArteryLTE.
#

DROP TABLE IF EXISTS artery_run;
DROP TABLE IF EXISTS vehicles;
DROP TABLE IF EXISTS sections;
DROP TABLE IF EXISTS traci;
DROP TABLE IF EXISTS meta;

CREATE TABLE artery_run (
     id INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
     run_number INT NOT NULL,
     network VARCHAR(80) NOT NULL,
     date TIMESTAMP NOT NULL
);

CREATE TABLE vehicles ( 
     id VARCHAR(200) NOT NULL PRIMARY KEY,
     type VARCHAR(200),
     length DOUBLE PRECISION NOT NULL
);

CREATE TABLE sections ( 
     id INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
     road_id VARCHAR(200) NOT NULL,
     lane_index INT UNSIGNED NOT NULL,
     length DOUBLE PRECISION NOT NULL, 
     UNIQUE(road_id,lane_index)
);

CREATE TABLE traci (
     id INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
     runid INT NOT NULL REFERENCES artery_run (id),
     simtime INT NOT NULL,
     vehicle INT NOT NULL REFERENCES vehicles (id), 
     speed DOUBLE PRECISION NOT NULL, 
     section INT NOT NULL REFERENCES sections (id), 
     position DOUBLE PRECISION NOT NULL
) ENGINE = MYISAM;

CREATE TABLE meta (
     id INT UNSIGNED AUTO_INCREMENT NOT NULL PRIMARY KEY,
     name VARCHAR(200) NOT NULL,
     value VARCHAR(200) NOT NULL
);
