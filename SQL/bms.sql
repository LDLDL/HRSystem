/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80017
 Source Host           : localhost:3306
 Source Schema         : bms

 Target Server Type    : MySQL
 Target Server Version : 80017
 File Encoding         : 65001

 Date: 17/06/2020 17:39:36
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for _bh
-- ----------------------------
DROP TABLE IF EXISTS `_bh`;
CREATE TABLE `_bh`  (
  `yg` int(11) NULL DEFAULT NULL,
  `bm` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 到期合同
-- ----------------------------
DROP TABLE IF EXISTS `到期合同`;
CREATE TABLE `到期合同`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `合同类型` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `生效日期` date NULL DEFAULT NULL,
  `结束日期` date NULL DEFAULT NULL,
  INDEX `员工编号`(`员工编号`) USING BTREE,
  CONSTRAINT `到期合同_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 员工记录
-- ----------------------------
DROP TABLE IF EXISTS `员工记录`;
CREATE TABLE `员工记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `员工姓名` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `员工性别` varchar(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `生日` date NULL DEFAULT NULL,
  `身份证` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `电话号码` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `地址` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `入职时间` date NULL DEFAULT NULL,
  `当值情况` varchar(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `部门编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `职位名称` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `学历情况` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`) USING BTREE,
  INDEX `职位名称`(`职位名称`, `部门编号`) USING BTREE,
  INDEX `学历情况`(`学历情况`) USING BTREE,
  CONSTRAINT `员工记录_ibfk_1` FOREIGN KEY (`职位名称`, `部门编号`) REFERENCES `职位` (`职位名称`, `部门编号`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `员工记录_ibfk_2` FOREIGN KEY (`学历情况`) REFERENCES `学历津贴` (`学历情况`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 培训记录
-- ----------------------------
DROP TABLE IF EXISTS `培训记录`;
CREATE TABLE `培训记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `培训内容` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `开始时间` date NULL DEFAULT NULL,
  `结束时间` date NULL DEFAULT NULL,
  `表现情况` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  INDEX `员工编号`(`员工编号`) USING BTREE,
  CONSTRAINT `培训记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 基本薪酬
-- ----------------------------
DROP TABLE IF EXISTS `基本薪酬`;
CREATE TABLE `基本薪酬`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `薪酬` double(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`) USING BTREE,
  CONSTRAINT `基本薪酬_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 奖惩记录
-- ----------------------------
DROP TABLE IF EXISTS `奖惩记录`;
CREATE TABLE `奖惩记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `日期` date NULL DEFAULT NULL,
  `奖惩金额` double(8, 2) NULL DEFAULT NULL,
  `原因` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  INDEX `奖惩记录`(`员工编号`) USING BTREE,
  CONSTRAINT `奖惩记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 学历津贴
-- ----------------------------
DROP TABLE IF EXISTS `学历津贴`;
CREATE TABLE `学历津贴`  (
  `学历情况` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `津贴` double(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`学历情况`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 工龄工资
-- ----------------------------
DROP TABLE IF EXISTS `工龄工资`;
CREATE TABLE `工龄工资`  (
  `工龄下限` tinyint(4) NOT NULL,
  `工龄上限` tinyint(4) NULL DEFAULT NULL,
  `所涨工资` double(8, 2) NULL DEFAULT NULL,
  UNIQUE INDEX `工龄下限`(`工龄下限`) USING BTREE,
  UNIQUE INDEX `工龄上限`(`工龄上限`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 有效合同
-- ----------------------------
DROP TABLE IF EXISTS `有效合同`;
CREATE TABLE `有效合同`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `合同类型` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `生效日期` date NULL DEFAULT NULL,
  `结束日期` date NULL DEFAULT NULL,
  INDEX `员工编号`(`员工编号`) USING BTREE,
  CONSTRAINT `有效合同_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 社保记录
-- ----------------------------
DROP TABLE IF EXISTS `社保记录`;
CREATE TABLE `社保记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `年份` int(11) NOT NULL,
  `月份` tinyint(4) NOT NULL,
  `状态` varchar(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`, `年份`, `月份`) USING BTREE,
  CONSTRAINT `社保记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 税前薪酬
-- ----------------------------
DROP TABLE IF EXISTS `税前薪酬`;
CREATE TABLE `税前薪酬`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `年份` int(11) NOT NULL,
  `月份` tinyint(4) NOT NULL,
  `税前工资` double(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`, `年份`, `月份`) USING BTREE,
  CONSTRAINT `税前薪酬_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 绩效记录
-- ----------------------------
DROP TABLE IF EXISTS `绩效记录`;
CREATE TABLE `绩效记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `年份` int(11) NOT NULL,
  `月份` tinyint(4) NOT NULL,
  `绩效得分` double(5, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`, `年份`, `月份`) USING BTREE,
  CONSTRAINT `绩效记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 绩效评判
-- ----------------------------
DROP TABLE IF EXISTS `绩效评判`;
CREATE TABLE `绩效评判`  (
  `得分下限` double(5, 2) NULL DEFAULT NULL,
  `得分上限` double(5, 2) NULL DEFAULT NULL,
  `绩效等级` varchar(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `工资上涨金额` double(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`绩效等级`) USING BTREE,
  UNIQUE INDEX `得分下限`(`得分下限`) USING BTREE,
  UNIQUE INDEX `得分上限`(`得分上限`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 考勤记录
-- ----------------------------
DROP TABLE IF EXISTS `考勤记录`;
CREATE TABLE `考勤记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `日期` date NOT NULL,
  `上班时间` time(0) NULL DEFAULT NULL,
  `下班时间` time(0) NULL DEFAULT NULL,
  `情况` varchar(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`员工编号`, `日期`) USING BTREE,
  CONSTRAINT `考勤记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 职位
-- ----------------------------
DROP TABLE IF EXISTS `职位`;
CREATE TABLE `职位`  (
  `职位名称` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `部门编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `职位工资` double(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`职位名称`, `部门编号`) USING BTREE,
  INDEX `部门编号`(`部门编号`) USING BTREE,
  CONSTRAINT `职位_ibfk_1` FOREIGN KEY (`部门编号`) REFERENCES `部门` (`部门编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 调岗记录
-- ----------------------------
DROP TABLE IF EXISTS `调岗记录`;
CREATE TABLE `调岗记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `调岗时间` timestamp(0) NULL DEFAULT 'now()' ON UPDATE CURRENT_TIMESTAMP(0),
  `前职位名称` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `前部门编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `现职位名称` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `现部门编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  INDEX `员工编号`(`员工编号`) USING BTREE,
  INDEX `前职位名称`(`前职位名称`, `前部门编号`) USING BTREE,
  INDEX `现职位名称`(`现职位名称`, `现部门编号`) USING BTREE,
  CONSTRAINT `调岗记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT,
  CONSTRAINT `调岗记录_ibfk_2` FOREIGN KEY (`前职位名称`, `前部门编号`) REFERENCES `职位` (`职位名称`, `部门编号`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `调岗记录_ibfk_3` FOREIGN KEY (`现职位名称`, `现部门编号`) REFERENCES `职位` (`职位名称`, `部门编号`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 调薪记录
-- ----------------------------
DROP TABLE IF EXISTS `调薪记录`;
CREATE TABLE `调薪记录`  (
  `员工编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `调整金额` double(8, 2) NULL DEFAULT NULL,
  `日期` date NULL DEFAULT 'curdate()',
  `备注` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  INDEX `员工编号`(`员工编号`) USING BTREE,
  CONSTRAINT `调薪记录_ibfk_1` FOREIGN KEY (`员工编号`) REFERENCES `员工记录` (`员工编号`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for 部门
-- ----------------------------
DROP TABLE IF EXISTS `部门`;
CREATE TABLE `部门`  (
  `部门编号` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `部门名称` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`部门编号`) USING BTREE,
  UNIQUE INDEX `部门名称`(`部门名称`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- View structure for 合同即将到期员工
-- ----------------------------
DROP VIEW IF EXISTS `合同即将到期员工`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `合同即将到期员工` AS select `有效合同`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`员工记录`.`身份证` AS `身份证`,`有效合同`.`合同类型` AS `合同类型`,`有效合同`.`生效日期` AS `生效日期`,`有效合同`.`结束日期` AS `结束日期` from (`有效合同` join `员工记录` on(((`有效合同`.`员工编号` = `员工记录`.`员工编号`) and ((to_days(`有效合同`.`结束日期`) - to_days(curdate())) < 30))));

-- ----------------------------
-- View structure for 员工
-- ----------------------------
DROP VIEW IF EXISTS `员工`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`员工记录`.`员工性别` AS `员工性别`,`员工记录`.`身份证` AS `身份证`,`员工记录`.`电话号码` AS `电话号码`,`员工记录`.`地址` AS `地址`,`员工记录`.`学历情况` AS `学历情况`,`员工记录`.`生日` AS `生日`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`员工记录`.`当值情况` AS `当值情况`,`员工记录`.`入职时间` AS `入职时间` from (`员工记录` join `部门`) where (`员工记录`.`部门编号` = `部门`.`部门编号`);

-- ----------------------------
-- View structure for 员工合同
-- ----------------------------
DROP VIEW IF EXISTS `员工合同`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工合同` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`有效合同`.`合同类型` AS `合同类型`,`有效合同`.`生效日期` AS `生效日期`,`有效合同`.`结束日期` AS `结束日期` from ((`有效合同` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `有效合同`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`)))) union all select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`到期合同`.`合同类型` AS `合同类型`,`到期合同`.`生效日期` AS `生效日期`,`到期合同`.`结束日期` AS `结束日期` from ((`到期合同` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `到期合同`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 员工培训
-- ----------------------------
DROP VIEW IF EXISTS `员工培训`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工培训` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`培训记录`.`培训内容` AS `培训内容`,`培训记录`.`开始时间` AS `开始时间`,`培训记录`.`结束时间` AS `结束时间`,`培训记录`.`表现情况` AS `表现情况` from ((`培训记录` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `培训记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 员工奖惩
-- ----------------------------
DROP VIEW IF EXISTS `员工奖惩`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工奖惩` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`奖惩记录`.`日期` AS `日期`,`奖惩记录`.`奖惩金额` AS `奖惩金额`,`奖惩记录`.`原因` AS `原因` from ((`奖惩记录` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `奖惩记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 员工工资
-- ----------------------------
DROP VIEW IF EXISTS `员工工资`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工工资` AS select `税前薪酬`.`员工编号` AS `员工编号`,`税前薪酬`.`年份` AS `年份`,`税前薪酬`.`月份` AS `月份`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`税前薪酬`.`税前工资` AS `税前工资` from ((`税前薪酬` join `员工记录`) join `部门` on(((`税前薪酬`.`员工编号` = `员工记录`.`员工编号`) and (`员工记录`.`部门编号` = `部门`.`部门编号`))));

-- ----------------------------
-- View structure for 员工社保
-- ----------------------------
DROP VIEW IF EXISTS `员工社保`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工社保` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`社保记录`.`年份` AS `年份`,`社保记录`.`月份` AS `月份`,`社保记录`.`状态` AS `状态` from ((`社保记录` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `社保记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 员工绩效
-- ----------------------------
DROP VIEW IF EXISTS `员工绩效`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工绩效` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`绩效记录`.`年份` AS `年份`,`绩效记录`.`月份` AS `月份`,`绩效记录`.`绩效得分` AS `绩效得分`,`绩效评判`.`绩效等级` AS `绩效等级` from (((`绩效记录` join `员工记录`) join `绩效评判`) join `部门` on(((`员工记录`.`员工编号` = `绩效记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`) and (`绩效记录`.`绩效得分` between `绩效评判`.`得分下限` and `绩效评判`.`得分上限`))));

-- ----------------------------
-- View structure for 员工考勤
-- ----------------------------
DROP VIEW IF EXISTS `员工考勤`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工考勤` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`考勤记录`.`日期` AS `日期`,`考勤记录`.`上班时间` AS `上班时间`,`考勤记录`.`下班时间` AS `下班时间`,`考勤记录`.`情况` AS `情况` from ((`考勤记录` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `考勤记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 员工调岗
-- ----------------------------
DROP VIEW IF EXISTS `员工调岗`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工调岗` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`调岗记录`.`调岗时间` AS `调岗时间`,`b1`.`部门名称` AS `前部门名称`,`调岗记录`.`前职位名称` AS `前职位名称`,`b2`.`部门名称` AS `现部门名称`,`调岗记录`.`现职位名称` AS `现职位名称` from (((`调岗记录` join `员工记录`) join `部门` `b1`) join `部门` `b2` on(((`员工记录`.`员工编号` = `调岗记录`.`员工编号`) and (`调岗记录`.`前部门编号` = `b1`.`部门编号`) and (`调岗记录`.`现部门编号` = `b2`.`部门编号`))));

-- ----------------------------
-- View structure for 员工调薪
-- ----------------------------
DROP VIEW IF EXISTS `员工调薪`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `员工调薪` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`部门`.`部门名称` AS `部门名称`,`员工记录`.`职位名称` AS `职位名称`,`调薪记录`.`日期` AS `日期`,`调薪记录`.`调整金额` AS `调整金额`,`调薪记录`.`备注` AS `备注` from ((`调薪记录` join `员工记录`) join `部门` on(((`员工记录`.`员工编号` = `调薪记录`.`员工编号`) and (`部门`.`部门编号` = `员工记录`.`部门编号`))));

-- ----------------------------
-- View structure for 无合同在职员工
-- ----------------------------
DROP VIEW IF EXISTS `无合同在职员工`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `无合同在职员工` AS select `员工记录`.`员工编号` AS `员工编号`,`员工记录`.`员工姓名` AS `员工姓名`,`员工记录`.`身份证` AS `身份证` from `员工记录` where (`员工记录`.`员工编号` in (select `有效合同`.`员工编号` from `有效合同`) is false and (`员工记录`.`当值情况` = '在职'));

-- ----------------------------
-- View structure for 部门职位
-- ----------------------------
DROP VIEW IF EXISTS `部门职位`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `部门职位` AS select `部门`.`部门编号` AS `部门编号`,`部门`.`部门名称` AS `部门名称`,`职位`.`职位名称` AS `职位名称`,`职位`.`职位工资` AS `职位工资` from (`部门` left join `职位` on((`部门`.`部门编号` = `职位`.`部门编号`))) order by `部门`.`部门编号`;

-- ----------------------------
-- Procedure structure for 增加员工
-- ----------------------------
DROP PROCEDURE IF EXISTS `增加员工`;
delimiter ;;
CREATE PROCEDURE `增加员工`(IN 员工编号 VARCHAR(20), 
	IN 员工姓名 VARCHAR(10),
	IN 员工性别 VARCHAR(2),
	IN 生日 DATE,
	IN 身份证 VARCHAR(20),
	IN 电话号码 VARCHAR(20),
	IN 地址 VARCHAR(50),
	IN 部门名称 VARCHAR(20),
	IN 职位名称 VARCHAR(20),
	IN 学历情况 VARCHAR(20))
BEGIN
	DECLARE bm VARCHAR(20);
	DECLARE jx DOUBLE(8,2);
	SELECT 部门编号 INTO bm FROM 部门 WHERE 部门名称 = 部门.`部门名称`;
	INSERT INTO 员工记录 VALUES(员工编号, 员工姓名, 员工性别, 生日, 身份证, 电话号码, 地址, CURDATE(), '在职', bm, 职位名称, 学历情况);
	SELECT 职位工资 INTO jx FROM 职位 WHERE (职位名称 = 职位.`职位名称` AND bm = 职位.`部门编号`);
	INSERT INTO 基本薪酬 VALUES(员工编号, jx);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 增加部门
-- ----------------------------
DROP PROCEDURE IF EXISTS `增加部门`;
delimiter ;;
CREATE PROCEDURE `增加部门`(IN 部门名称 VARCHAR(20))
BEGIN
	DECLARE _bb INT;
	SELECT bm INTO _bb FROM _bh;
	INSERT INTO 部门 VALUES(CONCAT('BM',_bb), 部门名称);
	UPDATE _bh SET bm = (_bb + 1)
	WHERE _bh.bm = _bb;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 打卡
-- ----------------------------
DROP PROCEDURE IF EXISTS `打卡`;
delimiter ;;
CREATE PROCEDURE `打卡`(IN 编号 VARCHAR(20))
BEGIN
	DECLARE _上班时间 TIME;

	SELECT bms.`考勤记录`.`上班时间` INTO _上班时间
	FROM bms.`考勤记录`
	WHERE bms.`考勤记录`.`员工编号` = 编号 AND bms.`考勤记录`.`日期` = CURRENT_DATE;

	 IF(_上班时间 IS NULL)
	 THEN
			SET _上班时间 = CURRENT_TIME;
			IF(_上班时间 > '08:30:00')
			THEN
				INSERT INTO bms.考勤记录(员工编号,日期,上班时间,情况) VALUES(编号,CURRENT_DATE,_上班时间,'迟到');
			ELSE
				INSERT INTO bms.考勤记录(员工编号,日期,上班时间) VALUES(编号,CURRENT_DATE,_上班时间);
			END IF;
	 END IF;
 
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 检查考勤记录
-- ----------------------------
DROP PROCEDURE IF EXISTS `检查考勤记录`;
delimiter ;;
CREATE PROCEDURE `检查考勤记录`(IN _date DATE)
BEGIN
DECLARE stopflag int DEFAULT FALSE;
DECLARE _员工编号 VARCHAR(20);
DECLARE 员工编号游标 CURSOR for SELECT 员工编号 FROM 员工记录 WHERE 当值情况 = '在职';
DECLARE CONTINUE HANDLER FOR NOT FOUND SET stopflag = TRUE;

OPEN 员工编号游标;
FETCH 员工编号游标 INTO _员工编号;
WHILE NOT stopflag DO
BEGIN

IF _员工编号 NOT IN (SELECT 员工编号 FROM 考勤记录 WHERE _date = 考勤记录.`日期`) THEN
INSERT INTO 考勤记录 VALUES(_员工编号, _date, NULL, NULL, '旷工');
END IF;

FETCH 员工编号游标 INTO _员工编号;
END;
END WHILE;
CLOSE 员工编号游标;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 生成某月社保
-- ----------------------------
DROP PROCEDURE IF EXISTS `生成某月社保`;
delimiter ;;
CREATE PROCEDURE `生成某月社保`(IN 当月 TINYINT)
BEGIN
DECLARE stopflag int DEFAULT FALSE;
DECLARE _员工编号 VARCHAR(20);
DECLARE 员工编号游标 CURSOR for SELECT `员工记录`.`员工编号` FROM `员工记录` WHERE 当值情况 = '在职';

DECLARE CONTINUE HANDLER FOR NOT FOUND SET stopflag = TRUE;

OPEN 员工编号游标;
FETCH 员工编号游标 INTO _员工编号;
WHILE NOT stopflag DO
BEGIN
IF _员工编号 NOT IN (SELECT 员工编号 FROM 社保记录 WHERE 社保记录.`月份` = 当月) THEN
INSERT INTO 社保记录 VALUES(_员工编号, 当月, '否');
END IF;

FETCH 员工编号游标 INTO _员工编号;
END;
END WHILE;
CLOSE 员工编号游标;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 编号调岗
-- ----------------------------
DROP PROCEDURE IF EXISTS `编号调岗`;
delimiter ;;
CREATE PROCEDURE `编号调岗`(IN 员工编号 VARCHAR(20),
	IN 调整后部门编号 VARCHAR(20),
	IN 调整后职位名称 VARCHAR(20))
BEGIN
	DECLARE 调整前部门编号 VARCHAR(20);
	DECLARE 调整前职位名称 VARCHAR(20);
	DECLARE axc DOUBLE(8,2);
	
	SELECT 部门编号,职位名称 INTO 调整前部门编号,调整前职位名称 FROM 员工记录 WHERE 员工记录.`员工编号` = 员工编号;
-- 	SELECT 部门编号 INTO 调整后部门编号 FROM 部门 WHERE 调整后部门编号 = 部门.`部门编号`;
	
	INSERT INTO 调岗记录 VALUES(员工编号, CURRENT_TIMESTAMP, 调整前职位名称, 调整前部门编号, 调整后职位名称, 调整后部门编号);
	UPDATE 员工记录 SET
	部门编号 = 调整后部门编号,
	职位名称 = 调整后职位名称
	WHERE 员工记录.`员工编号` = 员工编号;
	
	SELECT 职位工资 INTO axc FROM 职位 WHERE 职位.`部门编号` = 调整后部门编号 AND 职位.`职位名称` = 调整后职位名称;
	CALL 编号调薪(员工编号, axc, '调岗自动调薪');
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 编号调薪
-- ----------------------------
DROP PROCEDURE IF EXISTS `编号调薪`;
delimiter ;;
CREATE PROCEDURE `编号调薪`(IN 员工编号 VARCHAR(20),
	IN 调整后薪酬 DOUBLE(8,2),
	IN 备注 VARCHAR(50))
BEGIN
	INSERT INTO 调薪记录 VALUES(
		员工编号,
		调整后薪酬 - (SELECT 薪酬 FROM 基本薪酬 WHERE 基本薪酬.`员工编号` = 员工编号),
		CURRENT_TIMESTAMP,
		备注
	);
	UPDATE 基本薪酬 SET
	薪酬 = 调整后薪酬
	WHERE 基本薪酬.`员工编号` = 员工编号;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 考勤奖惩
-- ----------------------------
DROP PROCEDURE IF EXISTS `考勤奖惩`;
delimiter ;;
CREATE PROCEDURE `考勤奖惩`(IN _date DATE)
BEGIN
DECLARE stopflag int DEFAULT FALSE;
DECLARE _员工编号 VARCHAR(20);
DECLARE 员工编号游标 CURSOR for SELECT 员工编号 FROM 考勤记录 WHERE _date = 考勤记录.`日期`;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET stopflag = TRUE;

OPEN 员工编号游标;
FETCH 员工编号游标 INTO _员工编号;
WHILE NOT stopflag DO
BEGIN
DECLARE _情况 VARCHAR(5);

SELECT 情况 INTO _情况 FROM 考勤记录 WHERE 考勤记录.`员工编号` = _员工编号 AND _date = 考勤记录.`日期`;

IF _情况 = '迟到' THEN
INSERT INTO 奖惩记录 VALUES(_员工编号, _date, -100, '迟到');
END IF;

IF _情况 = '早退' THEN
INSERT INTO 奖惩记录 VALUES(_员工编号, _date, -100, '早退');
END IF;

IF _情况 = '迟到和早退' THEN
INSERT INTO 奖惩记录 VALUES(_员工编号, _date, -200, '迟到和早退');
END IF;

IF _情况 = '旷工' THEN
INSERT INTO 奖惩记录 VALUES(_员工编号, _date, -200, '旷工');
END IF;

FETCH 员工编号游标 INTO _员工编号;
END;
END WHILE;
CLOSE 员工编号游标;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 计算税前薪酬
-- ----------------------------
DROP PROCEDURE IF EXISTS `计算税前薪酬`;
delimiter ;;
CREATE PROCEDURE `计算税前薪酬`(IN 当年 INT,IN 当月 TINYINT)
BEGIN
	DECLARE stopflag int DEFAULT FALSE;
	DECLARE _员工编号 VARCHAR(20);
	DECLARE 员工编号游标 CURSOR for SELECT `员工记录`.`员工编号` FROM `员工记录` WHERE 当值情况 = '在职';
	
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET stopflag = TRUE;
	
	OPEN 员工编号游标;
	FETCH 员工编号游标 INTO _员工编号;
	WHILE NOT stopflag DO
		BEGIN
			DECLARE 工资 DOUBLE(8,2) DEFAULT 0;			
			DECLARE 工龄 TINYINT DEFAULT 0;
			DECLARE 学历 VARCHAR(20);
			DECLARE _津贴 DOUBLE(8,2) DEFAULT 0;
			DECLARE 目前工龄工资 DOUBLE(8,2) DEFAULT 0;
			DECLARE _绩效得分 DOUBLE(5,2) DEFAULT -1;
			DECLARE _绩效所得工资 DOUBLE(8,2) DEFAULT 0;
			DECLARE _奖惩金额 DOUBLE(8,2) DEFAULT 0;
			DECLARE _基础工资 DOUBLE(8,2) DEFAULT 0;
			
			/*获取工龄, 学历*/
			
			SELECT TIMESTAMPDIFF(YEAR,`入职时间`,CURDATE()) ,`员工记录`.`学历情况` INTO  工龄, 学历
			FROM `员工记录`
			WHERE `员工记录`.`员工编号` = _员工编号;
-- 			
-- 			
-- 			/*获取目前工龄工资*/
			SELECT 所涨工资 INTO 目前工龄工资 
			FROM `工龄工资` 
			WHERE 工龄 BETWEEN `工龄工资`.`工龄下限` AND `工龄工资`.`工龄上限`;
-- -- 			
-- -- 			
-- -- 			
-- -- /*获取学历津贴*/
			SELECT `学历津贴`.`津贴` INTO _津贴
			FROM `学历津贴`
			WHERE `学历津贴`.`学历情况` = 学历;
-- -- 			
-- -- 			
-- -- 	/*获得绩效得分*/		
			SELECT `绩效记录`.`绩效得分`INTO _绩效得分
			FROM `绩效记录`
			WHERE `绩效记录`.`员工编号` = _员工编号 
			AND `绩效记录`.`月份` = 当月 
			AND `绩效记录`.`年份` = 当年;
-- -- 			
			SELECT _绩效得分;
-- -- /*获得绩效所得工资*/
			IF(_绩效得分 != -1)
			THEN
			SELECT `绩效评判`.`工资上涨金额` INTO _绩效所得工资
			FROM `绩效评判`
			WHERE _绩效得分 BETWEEN `绩效评判`.`得分下限` AND `绩效评判`.`得分上限` ;
			END IF;
-- -- 			
-- -- 			
-- -- 			/*获取奖惩情况*/
			SELECT SUM(`奖惩记录`.`奖惩金额`) INTO _奖惩金额
			FROM `奖惩记录`
			WHERE `奖惩记录`.`员工编号` = _员工编号 
			AND MONTH(`奖惩记录`.`日期`) = 当月 
			AND YEAR(`奖惩记录`.`日期`) = 当年;
-- -- 					
-- -- 			
-- -- 			/*获取基础工资*/
			SELECT `基本薪酬`.`薪酬` INTO _基础工资
			FROM `基本薪酬`
			WHERE `基本薪酬`.`员工编号` = _员工编号;
-- -- 			
-- -- 			/*插入税前工资*/
			SET 工资 = IFNULL(_基础工资,0) +IFNULL(目前工龄工资,0) +IFNULL(_绩效所得工资,0)  + IFNULL(_奖惩金额,0);
			INSERT INTO 税前薪酬 VALUE(_员工编号,当年,当月,工资);
			FETCH 员工编号游标 INTO _员工编号;
		END;
	END WHILE;
	CLOSE 员工编号游标;
	
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 转移到期合同
-- ----------------------------
DROP PROCEDURE IF EXISTS `转移到期合同`;
delimiter ;;
CREATE PROCEDURE `转移到期合同`()
BEGIN
INSERT INTO 到期合同
SELECT 员工编号,合同类型,生效日期,结束日期 FROM 有效合同
WHERE DATEDIFF(有效合同.`结束日期`,CURDATE()) < 0;

DELETE FROM 有效合同“
WHERE DATEDIFF(有效合同.`结束日期`,CURDATE()) < 0;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 退签
-- ----------------------------
DROP PROCEDURE IF EXISTS `退签`;
delimiter ;;
CREATE PROCEDURE `退签`(IN 编号 VARCHAR(20))
BEGIN
DECLARE _下班时间 TIME;
DECLARE _情况 VARCHAR(20);

SELECT bms.`考勤记录`.`下班时间` INTO _下班时间
FROM bms.`考勤记录`
WHERE bms.`考勤记录`.`员工编号` = 编号  AND bms.`考勤记录`.`日期` = CURRENT_DATE;

 IF(_下班时间 IS NULL)
 THEN
		SET _下班时间 = TIME(NOW());
		IF(_下班时间 < '22:30:00') -- 要改
		THEN
			SELECT bms.`考勤记录`.`情况` INTO _情况
			FROM  bms.`考勤记录`
			WHERE bms.`考勤记录`.`员工编号` = 编号 AND bms.`考勤记录`.`日期` = CURRENT_DATE;
			
			IF(_情况 is NULL)
			THEN
					UPDATE  bms.`考勤记录` SET 下班时间 =  _下班时间, 情况 = '早退'
					WHERE  bms.`考勤记录`.`员工编号` = 编号 AND bms.`考勤记录`.`日期` = CURRENT_DATE;
			ELSE
					
					UPDATE  bms.`考勤记录` SET 下班时间 =  _下班时间,情况 = CONCAT(_情况,'和','早退')
					WHERE  bms.`考勤记录`.`员工编号` = 编号 AND bms.`考勤记录`.`日期` = CURRENT_DATE;
			END IF;
			
		ELSE
				UPDATE  bms.`考勤记录` SET 下班时间 =  _下班时间
				WHERE  bms.`考勤记录`.`员工编号` = 编号 AND bms.`考勤记录`.`日期` = CURRENT_DATE;
		END IF;
 END IF;
 
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 部门撤销
-- ----------------------------
DROP PROCEDURE IF EXISTS `部门撤销`;
delimiter ;;
CREATE PROCEDURE `部门撤销`(IN _部门编号 VARCHAR(20))
BEGIN
		
		UPDATE bms.`员工记录` SET  bms.`员工记录`.`部门编号` = NULL, bms.`员工记录`.`职位名称`=NULL
		WHERE bms.`员工记录`.`当值情况`='离职';
		
		DELETE 
		fROM bms.`部门`
		WHERE bms.`部门`.`部门编号` = _部门编号;
	END
;;
delimiter ;

-- ----------------------------
-- Event structure for 导入考勤奖惩
-- ----------------------------
DROP EVENT IF EXISTS `导入考勤奖惩`;
delimiter ;;
CREATE EVENT `导入考勤奖惩`
ON SCHEDULE
EVERY '1' MONTH STARTS '2020-07-01 00:00:00'
ON COMPLETION PRESERVE
DO CALL 考勤奖惩(SUBDATE(CURDATE(),1))
;;
delimiter ;

-- ----------------------------
-- Event structure for 月结工资
-- ----------------------------
DROP EVENT IF EXISTS `月结工资`;
delimiter ;;
CREATE EVENT `月结工资`
ON SCHEDULE
EVERY '1' MONTH STARTS '2020-07-01 00:00:00'
ON COMPLETION PRESERVE
DO CALL 计算税前薪酬(YEAR(SUBDATE(CURRENT_DATE,1)),MONTH(SUBDATE(CURRENT_DATE,1)))
;;
delimiter ;

-- ----------------------------
-- Event structure for 每日检查到期合同
-- ----------------------------
DROP EVENT IF EXISTS `每日检查到期合同`;
delimiter ;;
CREATE EVENT `每日检查到期合同`
ON SCHEDULE
EVERY '1' DAY STARTS '2020-06-19 00:00:00'
ON COMPLETION PRESERVE
DO CALL  转移到期合同()
;;
delimiter ;

-- ----------------------------
-- Event structure for 每日检查考勤
-- ----------------------------
DROP EVENT IF EXISTS `每日检查考勤`;
delimiter ;;
CREATE EVENT `每日检查考勤`
ON SCHEDULE
EVERY '1' DAY STARTS '2020-06-19 00:00:00'
ON COMPLETION PRESERVE
DO CALL  检查考勤记录(SUBDATE(CURDATE(),1))
;;
delimiter ;

-- ----------------------------
-- Event structure for 每月生成社保记录
-- ----------------------------
DROP EVENT IF EXISTS `每月生成社保记录`;
delimiter ;;
CREATE EVENT `每月生成社保记录`
ON SCHEDULE
EVERY '1' MONTH STARTS '2020-07-01 00:00:00'
ON COMPLETION PRESERVE
DO CALL 生成某月社保(MONTH(CURRENT_DATE))
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
