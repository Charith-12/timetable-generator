-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Oct 04, 2023 at 02:11 AM
-- Server version: 8.0.34-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `university`
--

-- --------------------------------------------------------

--
-- Table structure for table `batches`
--

CREATE TABLE `batches` (
  `batch_id` int NOT NULL,
  `batch_name` varchar(255) DEFAULT NULL,
  `no_students` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `batches`
--

INSERT INTO `batches` (`batch_id`, `batch_name`, `no_students`) VALUES
(1, 'B1', 16),
(2, 'B2', 30);

-- --------------------------------------------------------

--
-- Table structure for table `bmallocations`
--

CREATE TABLE `bmallocations` (
  `batch_id` int NOT NULL,
  `mod_id` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `bmallocations`
--

INSERT INTO `bmallocations` (`batch_id`, `mod_id`) VALUES
(1, 'M1'),
(1, 'M2'),
(1, 'M3'),
(1, 'M4'),
(2, 'M5'),
(2, 'M6'),
(2, 'M7'),
(2, 'M8');

-- --------------------------------------------------------

--
-- Table structure for table `classrooms`
--

CREATE TABLE `classrooms` (
  `room_id` varchar(255) NOT NULL,
  `room_no` int NOT NULL,
  `capacity` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `classrooms`
--

INSERT INTO `classrooms` (`room_id`, `room_no`, `capacity`) VALUES
('C1', 1, 50),
('C2', 2, 50);

-- --------------------------------------------------------

--
-- Table structure for table `constraints`
--

CREATE TABLE `constraints` (
  `const_id` int NOT NULL,
  `start_time` int DEFAULT NULL,
  `end_time` int DEFAULT NULL,
  `no_of_days` int DEFAULT '5'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `constraints`
--

INSERT INTO `constraints` (`const_id`, `start_time`, `end_time`, `no_of_days`) VALUES
(1, 9, 17, 5);

-- --------------------------------------------------------

--
-- Table structure for table `costs`
--

CREATE TABLE `costs` (
  `cost_id` int NOT NULL,
  `new_lec` int DEFAULT '500000',
  `wl_ext` int DEFAULT '10000',
  `time_ext` int DEFAULT '4000',
  `new_room` int DEFAULT '1000000'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `costs`
--

INSERT INTO `costs` (`cost_id`, `new_lec`, `wl_ext`, `time_ext`, `new_room`) VALUES
(1, 100, 10000, 4000, 1000000);

-- --------------------------------------------------------

--
-- Table structure for table `edges`
--

CREATE TABLE `edges` (
  `lec_id` varchar(255) NOT NULL,
  `mod_id` varchar(255) NOT NULL,
  `color_id` int NOT NULL,
  `batch_id` int NOT NULL,
  `timeslot` int NOT NULL,
  `room_id` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `edges`
--

INSERT INTO `edges` (`lec_id`, `mod_id`, `color_id`, `batch_id`, `timeslot`, `room_id`) VALUES
('L1', 'M2', 1, 1, 1, 'C1'),
('L1', 'M2', 2, 1, 2, 'C1'),
('L2', 'M5', 1, 2, 1, 'C2'),
('L2', 'M5', 2, 2, 2, 'C2'),
('L2', 'M5', 3, 2, 3, 'C1'),
('L3', 'M3', 4, 1, 4, 'C1'),
('L3', 'M3', 5, 1, 5, 'C1'),
('L3', 'M3', 6, 1, 6, 'C1'),
('L3', 'M7', 1, 2, 8, 'C2'),
('L3', 'M7', 2, 2, 10, 'C2'),
('L3', 'M7', 3, 2, 12, 'C1'),
('L4', 'M1', 5, 1, 14, 'C1'),
('L4', 'M1', 6, 1, 15, 'C1'),
('L4', 'M1', 7, 1, 7, 'C1'),
('L4', 'M4', 1, 1, 8, 'C1'),
('L4', 'M4', 2, 1, 10, 'C1'),
('L4', 'M8', 3, 2, 13, 'C1'),
('L4', 'M8', 4, 2, 4, 'C2'),
('NH~1', 'M6', 1, 2, 9, 'C1'),
('NH~1', 'M6', 2, 2, 11, 'C1');

-- --------------------------------------------------------

--
-- Table structure for table `lecmodallocations`
--

CREATE TABLE `lecmodallocations` (
  `lec_id` varchar(255) NOT NULL,
  `mod_id` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lecmodallocations`
--

INSERT INTO `lecmodallocations` (`lec_id`, `mod_id`) VALUES
('L1', 'M1'),
('L1', 'M2'),
('L2', 'M5'),
('L2', 'M6'),
('L3', 'M3'),
('L3', 'M7'),
('L4', 'M1'),
('L4', 'M4'),
('L4', 'M8');

-- --------------------------------------------------------

--
-- Table structure for table `lecturers`
--

CREATE TABLE `lecturers` (
  `lec_id` varchar(255) NOT NULL,
  `lec_name` varchar(255) DEFAULT NULL,
  `no_subjects` int DEFAULT '0',
  `wl` int DEFAULT '0',
  `max_hours` int DEFAULT '168',
  `pay_rate` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lecturers`
--

INSERT INTO `lecturers` (`lec_id`, `lec_name`, `no_subjects`, `wl`, `max_hours`, `pay_rate`) VALUES
('L1', 'W.A.Wickrama', 0, 0, 168, 1000),
('L2', 'L.T.Senevirathne', 0, 0, 3, 1000),
('L3', 'J.Ramanayake', 0, 0, 168, 1000),
('L4', 'P.Lakmal', 0, 0, 168, 800);

-- --------------------------------------------------------

--
-- Table structure for table `lecunavailabletimes`
--

CREATE TABLE `lecunavailabletimes` (
  `lec_id` varchar(255) NOT NULL,
  `pos_id` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lecunavailabletimes`
--

INSERT INTO `lecunavailabletimes` (`lec_id`, `pos_id`) VALUES
('L1', 100),
('L1', 101),
('L1', 102),
('L1', 103),
('L1', 104),
('L1', 105),
('L1', 106),
('L1', 107),
('L1', 108),
('L1', 109),
('L1', 110),
('L1', 111),
('L1', 112),
('L1', 113),
('L1', 114),
('L1', 115),
('L1', 116),
('L1', 117),
('L1', 118),
('L1', 119),
('L1', 120),
('L1', 121),
('L1', 122),
('L1', 123);

-- --------------------------------------------------------

--
-- Table structure for table `lmallocations`
--

CREATE TABLE `lmallocations` (
  `lec_id` varchar(255) NOT NULL,
  `mod_id` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lmallocations`
--

INSERT INTO `lmallocations` (`lec_id`, `mod_id`) VALUES
('L4', 'M1'),
('L1', 'M2'),
('L3', 'M3'),
('L4', 'M4'),
('L2', 'M5'),
('NH~1', 'M6'),
('L3', 'M7'),
('L4', 'M8');

-- --------------------------------------------------------

--
-- Table structure for table `modules`
--

CREATE TABLE `modules` (
  `mod_id` varchar(255) NOT NULL,
  `mod_name` varchar(255) DEFAULT NULL,
  `credits` int NOT NULL,
  `batch_id` int DEFAULT NULL,
  `al_status` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `modules`
--

INSERT INTO `modules` (`mod_id`, `mod_name`, `credits`, `batch_id`, `al_status`) VALUES
('M1', 'Algebra', 3, 1, NULL),
('M2', 'Physics', 2, 1, NULL),
('M3', 'Statistics', 3, 1, NULL),
('M4', 'Programming F.', 2, 1, NULL),
('M5', 'Networks I', 3, 2, NULL),
('M6', 'Telecom', 2, 2, NULL),
('M7', 'Optical C.', 3, 2, NULL),
('M8', 'Wireless C.', 2, 2, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `optimizedpositions`
--

CREATE TABLE `optimizedpositions` (
  `timeslot` int NOT NULL,
  `pos_id` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `optimizedpositions`
--

INSERT INTO `optimizedpositions` (`timeslot`, `pos_id`) VALUES
(1, 311),
(2, 213),
(3, 511),
(4, 314),
(5, 412),
(6, 110),
(7, 309),
(8, 414),
(9, 315),
(10, 413),
(11, 509),
(12, 512);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `batches`
--
ALTER TABLE `batches`
  ADD PRIMARY KEY (`batch_id`);

--
-- Indexes for table `bmallocations`
--
ALTER TABLE `bmallocations`
  ADD PRIMARY KEY (`batch_id`,`mod_id`);

--
-- Indexes for table `classrooms`
--
ALTER TABLE `classrooms`
  ADD PRIMARY KEY (`room_id`),
  ADD UNIQUE KEY `room_no unique index` (`room_no`);

--
-- Indexes for table `constraints`
--
ALTER TABLE `constraints`
  ADD PRIMARY KEY (`const_id`);

--
-- Indexes for table `costs`
--
ALTER TABLE `costs`
  ADD PRIMARY KEY (`cost_id`);

--
-- Indexes for table `edges`
--
ALTER TABLE `edges`
  ADD PRIMARY KEY (`lec_id`,`mod_id`,`color_id`);

--
-- Indexes for table `lecmodallocations`
--
ALTER TABLE `lecmodallocations`
  ADD PRIMARY KEY (`lec_id`,`mod_id`);

--
-- Indexes for table `lecturers`
--
ALTER TABLE `lecturers`
  ADD PRIMARY KEY (`lec_id`);

--
-- Indexes for table `lecunavailabletimes`
--
ALTER TABLE `lecunavailabletimes`
  ADD PRIMARY KEY (`lec_id`,`pos_id`);

--
-- Indexes for table `lmallocations`
--
ALTER TABLE `lmallocations`
  ADD PRIMARY KEY (`mod_id`);

--
-- Indexes for table `modules`
--
ALTER TABLE `modules`
  ADD PRIMARY KEY (`mod_id`);

--
-- Indexes for table `optimizedpositions`
--
ALTER TABLE `optimizedpositions`
  ADD PRIMARY KEY (`timeslot`,`pos_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `classrooms`
--
ALTER TABLE `classrooms`
  MODIFY `room_no` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `constraints`
--
ALTER TABLE `constraints`
  MODIFY `const_id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `costs`
--
ALTER TABLE `costs`
  MODIFY `cost_id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
