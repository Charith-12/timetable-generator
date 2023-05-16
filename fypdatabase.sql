--- MySQL dump 10.13  Distrib 8.0.32, for Linux (x86_64)
--
-- Host: localhost	Database: fypdatabase
-- ------------------------------------------------------
-- Server version    8.0.32-0ubuntu0.22.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `batch_modules`
--

DROP TABLE IF EXISTS `batch_modules`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `batch_modules` (
  `batch_name` char(30) NOT NULL,
  `module_code` varchar(6) NOT NULL,
  `batchmodID` int NOT NULL AUTO_INCREMENT,
  `batchid` int NOT NULL,
  PRIMARY KEY (`batchmodID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `batch_modules`
--

LOCK TABLES `batch_modules` WRITE;
/*!40000 ALTER TABLE `batch_modules` DISABLE KEYS */;
/*!40000 ALTER TABLE `batch_modules` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `batches`
--

DROP TABLE IF EXISTS `batches`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `batches` (
  `batch_name` char(30) NOT NULL,
  `no_students` int NOT NULL,
  `batchid` int NOT NULL,
  PRIMARY KEY (`batchid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `batches`
--

LOCK TABLES `batches` WRITE;
/*!40000 ALTER TABLE `batches` DISABLE KEYS */;
/*!40000 ALTER TABLE `batches` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `classrooms`
--

DROP TABLE IF EXISTS `classrooms`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `classrooms` (
  `room_id` varchar(225) NOT NULL,
  `room_no` int NOT NULL AUTO_INCREMENT,
  `capacity` int DEFAULT NULL,
  PRIMARY KEY (`room_id`),
  UNIQUE KEY `room_no` (`room_no`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `classrooms`
--

LOCK TABLES `classrooms` WRITE;
/*!40000 ALTER TABLE `classrooms` DISABLE KEYS */;
/*!40000 ALTER TABLE `classrooms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `constraints`
--

DROP TABLE IF EXISTS `constraints`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `constraints` (
  `costToExtendDays` int DEFAULT NULL,
  `costToExtendHours` int DEFAULT NULL,
  `costToHire` int DEFAULT NULL,
  `intervalBetweenSlots` int DEFAULT NULL,
  `openTime` int DEFAULT NULL,
  `closeTime` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `constraints`
--

LOCK TABLES `constraints` WRITE;
/*!40000 ALTER TABLE `constraints` DISABLE KEYS */;
/*!40000 ALTER TABLE `constraints` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lec_modules`
--

DROP TABLE IF EXISTS `lec_modules`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lec_modules` (
  `lec_id` varchar(200) NOT NULL,
  `module_code` varchar(45) NOT NULL,
  `modLecID` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`modLecID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lec_modules`
--

LOCK TABLES `lec_modules` WRITE;
/*!40000 ALTER TABLE `lec_modules` DISABLE KEYS */;
/*!40000 ALTER TABLE `lec_modules` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lecturers`
--

DROP TABLE IF EXISTS `lecturers`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `lecturers` (
  `lec_id` varchar(300) NOT NULL,
  `lec_name` varchar(200) NOT NULL,
  `max_hours` int NOT NULL,
  `pay_rate` int DEFAULT NULL,
  PRIMARY KEY (`lec_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `lecturers`
--

LOCK TABLES `lecturers` WRITE;
/*!40000 ALTER TABLE `lecturers` DISABLE KEYS */;
/*!40000 ALTER TABLE `lecturers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `master_tt`
--

DROP TABLE IF EXISTS `master_tt`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `master_tt` (
  `batch` varchar(45) DEFAULT NULL,
  `module` varchar(45) DEFAULT NULL,
  `lecturer` varchar(45) DEFAULT NULL,
  `hour` varchar(45) DEFAULT NULL,
  `day` varchar(45) DEFAULT NULL,
  `classroom` varchar(45) DEFAULT NULL,
  `slot_id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`slot_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `master_tt`
--

LOCK TABLES `master_tt` WRITE;
/*!40000 ALTER TABLE `master_tt` DISABLE KEYS */;
/*!40000 ALTER TABLE `master_tt` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `module`
--

DROP TABLE IF EXISTS `module`;
/*!40101 SET @saved_cs_client 	= @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `module` (
  `mod_code` varchar(50) NOT NULL,
  `mod_name` varchar(50) NOT NULL,
  `credits` int NOT NULL,
  PRIMARY KEY (`mod_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `module`
--

LOCK TABLES `module` WRITE;
/*!40000 ALTER TABLE `module` DISABLE KEYS */;
/*!40000 ALTER TABLE `module` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-03-27 14:13:15
