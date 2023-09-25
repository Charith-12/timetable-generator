-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Sep 26, 2023 at 12:30 AM
-- Server version: 8.0.33-0ubuntu0.22.04.2
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
(2, 'M3'),
(2, 'M4');

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
('R1', 3, 20),
('R2', 4, 50),
('R3', 5, 150);

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
('L1', 'M1', 4, 1, 4, 'R1'),
('L1', 'M1', 5, 1, 5, 'R1'),
('L1', 'M1', 6, 1, 6, 'R1'),
('L1', 'M2', 2, 1, 2, 'R1'),
('L1', 'M2', 3, 1, 3, 'R1'),
('L1', 'M3', 7, 2, 7, 'R2'),
('L1', 'M3', 8, 2, 8, 'R2'),
('L1', 'M3', 9, 2, 9, 'R2'),
('L1', 'M4', 1, 2, 1, 'R2');

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
('L1', 'M3'),
('L1', 'M4'),
('L2', 'M1'),
('L2', 'M2'),
('L2', 'M3'),
('L2', 'M4');

-- --------------------------------------------------------

--
-- Table structure for table `lecturers`
--

CREATE TABLE `lecturers` (
  `lec_id` varchar(255) NOT NULL,
  `lec_name` varchar(255) DEFAULT NULL,
  `no_subjects` int DEFAULT '0',
  `wl` int DEFAULT '0',
  `max_hours` int DEFAULT NULL,
  `pay_rate` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lecturers`
--

INSERT INTO `lecturers` (`lec_id`, `lec_name`, `no_subjects`, `wl`, `max_hours`, `pay_rate`) VALUES
('L1', 'Sunil', 0, 0, 25, 1000),
('L2', 'Kanthi', 0, 0, 40, 7500);

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
('L1', 'M1'),
('L1', 'M2'),
('L1', 'M3'),
('L1', 'M4');

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
('M1', 'MATHS', 3, 1, NULL),
('M2', 'SCIENCE', 2, 1, NULL),
('M3', 'ART', 3, 2, NULL),
('M4', 'HISTORY', 1, 2, NULL);

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
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `classrooms`
--
ALTER TABLE `classrooms`
  MODIFY `room_no` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
