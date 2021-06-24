-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Máy chủ: 127.0.0.1
-- Thời gian đã tạo: Th6 23, 2021 lúc 12:47 PM
-- Phiên bản máy phục vụ: 10.4.11-MariaDB
-- Phiên bản PHP: 7.4.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Cơ sở dữ liệu: `rfid_mysql2`
--

-- --------------------------------------------------------

--
-- Cấu trúc bảng cho bảng `table_the_iot_projects`
--

CREATE TABLE `table_the_iot_projects` (
  `name` varchar(100) NOT NULL,
  `id` varchar(100) NOT NULL,
  `gender` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `mobile` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Đang đổ dữ liệu cho bảng `table_the_iot_projects`
--

INSERT INTO `table_the_iot_projects` (`name`, `id`, `gender`, `email`, `mobile`) VALUES
('VD lap trinh 7', '12715413', 'Female', 'vdlaptrinh@gmail.com', '0909123456'),
('VD Lap Trinh 9', '12715493', 'Female', 'vdlaptrinh@gmail.com', '0919123456'),
('VD Lap Trinh 8', '12715501', 'Male', 'vdlaptrinh@gmail.com', '0919123456'),
('VD lap trinh 5', '15198951', 'Female', 'vdlaptrinh@gmail.com', '0909123456'),
('VD Lap Trinh 10', '15650647', 'Male', 'vdlaptrinh@gmail.com', '0919123456'),
('VD lap trinh 6', '2243724', 'Male', 'vdlaptrinh@gmail.com', '0909123456'),
('VD lap trinh 4', '2249554', 'Male', 'vdlaptrinh@gmail.com', '0909123456'),
('VD Lap Trinh 1', '4448724', 'Male', 'vdlaptrinh@gmail.com', '0919123456'),
('VD lap trinh 3', '8198525', 'Male', 'vdlaptrinh@gmail.com', '0909123456'),
('VD lap trinh 2', '911277', 'Male', 'vdlaptrinh@gmail.com', '0909123456');

--
-- Chỉ mục cho các bảng đã đổ
--

--
-- Chỉ mục cho bảng `table_the_iot_projects`
--
ALTER TABLE `table_the_iot_projects`
  ADD PRIMARY KEY (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
