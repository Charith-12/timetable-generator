-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jan 28, 2023 at 03:05 AM
-- Server version: 8.0.32-0buntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.10

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
(1, 'ICE - Batch 6', 16),
(2, 'Tele Eng - Batch 6', 120),
(3, 'Civil Eng - Batch 6', 48),
(4, 'Mech Eng - Batch 6', 32);

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
('Audi04', 5, 30),
('Audi05', 4, 250),
('Audi08', 3, 20),
('FF2', 6, 150),
('FF4', 2, 80),
('GF4', 1, 80);

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
('L001', 'ECS100', 3, 1, 3, 'Audi08'),
('L001', 'ECS100', 4, 1, 4, 'Audi08'),
('L001', 'ECS101', 1, 1, 1, 'Audi08'),
('L001', 'ECS101', 2, 1, 2, 'Audi08'),
('L002', 'EMA200', 2, 1, 7, 'Audi08'),
('L002', 'EMA200', 3, 1, 8, 'Audi08'),
('L002', 'EMA202', 4, 2, 4, 'FF2'),
('L002', 'EMA202', 5, 2, 5, 'FF2'),
('L002', 'EMA204', 1, 2, 1, 'FF2'),
('L003', 'EMN300', 1, 2, 6, 'FF2'),
('L003', 'EMN300', 2, 2, 2, 'FF2');

-- --------------------------------------------------------

--
-- Table structure for table `lecturers`
--

CREATE TABLE `lecturers` (
  `lec_id` varchar(255) NOT NULL,
  `lec_name` varchar(255) DEFAULT NULL,
  `no_subjects` int NOT NULL,
  `wl` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `lecturers`
--

INSERT INTO `lecturers` (`lec_id`, `lec_name`, `no_subjects`, `wl`) VALUES
('L001', 'W.A.Jananayake', 2, 4),
('L002', 'J.K.Kudaligama', 3, 5),
('L003', 'R.P.Gunasena', 1, 2);

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
('L001', 'ECS100'),
('L001', 'ECS101'),
('L002', 'EMA200'),
('L002', 'EMA202'),
('L002', 'EMA204'),
('L003', 'EMN300');

-- --------------------------------------------------------

--
-- Table structure for table `modules`
--

CREATE TABLE `modules` (
  `mod_id` varchar(255) NOT NULL,
  `mod_name` varchar(255) DEFAULT NULL,
  `credits` int NOT NULL,
  `batch_id` int NOT NULL,
  `al_status` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `modules`
--

INSERT INTO `modules` (`mod_id`, `mod_name`, `credits`, `batch_id`, `al_status`) VALUES
('ECS100', 'Operating Systems', 2, 1, 1),
('ECS101', 'Data Structures', 2, 1, 1),
('EMA200', 'Linear Algebra', 2, 1, 1),
('EMA202', 'Numerical Methods', 2, 2, 1),
('EMA204', 'Calculus', 1, 2, 1),
('EMN300', 'Statistics', 2, 2, 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `batches`
--
ALTER TABLE `batches`
  ADD PRIMARY KEY (`batch_id`);

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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
