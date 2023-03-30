#!/bin/bash
###
# @Descripttion:
# @version: 1.0
# @Author: Lance
# @Date: 2021-07-07 09:52:14
 # @LastEditors: Lance
 # @LastEditTime: 2023-03-30 11:24:49
###
Target_hostname='root'
Target_IP='192.168.1.108'
Target_PATH='/root/led'
Target_password='hesiqi'
Local_PATH='./bin'
Local_FILE='*'
echo "Start sending \"$Local_PATH/$Local_FILE\" files to $Target_hostname@$Target_IP:$Target_PATH"
sshpass -p $Target_password scp $Local_PATH/$Local_FILE $Target_hostname@$Target_IP:$Target_PATH
echo "End of sending"
