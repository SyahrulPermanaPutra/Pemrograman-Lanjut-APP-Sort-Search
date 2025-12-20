/*
SQLyog Community v12.4.0 (64 bit)
MySQL - 10.4.32-MariaDB : Database - jobhunter_db
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`jobhunter_db` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci */;

USE `jobhunter_db`;

/*Table structure for table `lowongan` */

DROP TABLE IF EXISTS `lowongan`;

CREATE TABLE `lowongan` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `posisi` varchar(255) NOT NULL,
  `perusahaan` varchar(255) NOT NULL,
  `jenis_pekerjaan` enum('Full-time','Part-time','Remote','Hybrid','Contract') NOT NULL,
  `level` enum('Junior','Middle','Senior','Lead','Manager','Director') NOT NULL,
  `jalan` text DEFAULT NULL,
  `kota` varchar(100) DEFAULT NULL,
  `provinsi` varchar(100) DEFAULT NULL,
  `kode_pos` varchar(10) DEFAULT NULL,
  `gaji_minimal` decimal(10,2) NOT NULL,
  `gaji_maksimal` decimal(10,2) NOT NULL,
  `tipe_gaji` varchar(50) DEFAULT 'Per bulan',
  `pengalaman_minimal` int(11) DEFAULT 0,
  `pendidikan_minimal` varchar(50) DEFAULT NULL,
  `bahasa` varchar(100) DEFAULT NULL,
  `asuransi_kesehatan` text DEFAULT NULL,
  `tunjangan_transport` tinyint(1) DEFAULT 0,
  `tunjangan_makan` tinyint(1) DEFAULT 0,
  `program_pensiun` text DEFAULT NULL,
  `pengembangan_karir` text DEFAULT NULL,
  `cuti_tahunan` int(11) DEFAULT 12,
  `deskripsi_pekerjaan` text DEFAULT NULL,
  `tanggal_post` date NOT NULL,
  `jumlah_pelamar` int(11) DEFAULT 0,
  `status_aktif` tinyint(1) DEFAULT 1,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_posisi` (`posisi`),
  KEY `idx_perusahaan` (`perusahaan`),
  KEY `idx_kota` (`kota`),
  KEY `idx_level` (`level`),
  KEY `idx_gaji` (`gaji_minimal`,`gaji_maksimal`),
  KEY `idx_status` (`status_aktif`)
) ENGINE=InnoDB AUTO_INCREMENT=40001 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

/*Data for the table `lowongan` */

LOCK TABLES `lowongan` WRITE;

UNLOCK TABLES;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
