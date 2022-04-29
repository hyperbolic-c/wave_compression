import math
from decimal import *

def float2bin(x, n):
	'''
	x : float type
	n : bins nums
	return : list type
	'''
	bins = []
	while n > 0:
		x = x * 2
		if x >= 1.0:
			bins.append(1)
		else:
			bins.append(0)
		x -= int(x)
		n -= 1
	# print(bins)
	return bins


def bin2float(bins):
	'''
	bins: list type
	return : float type
	'''
	c = []
	f = -1
	for i in range(len(bins)):
		c.append(f)
		f -= 1

	num = Decimal(0.0)
	for i in range(len(bins)):
		num += Decimal(bins[i] * 2**c[i])
	# print(num)
	return num


def adaptive_AC_encode(strList, char, char_frequence, char_list):
	'''
	自适应模式算术编码
	strList: 要进行编码的字符串序列
	char: 编码字符初始概率空间
	char_frequence : 字符出现频率
	char_list : 编码过程中概率空间的变化序列
	return : code_length: 编码长度
			 bins: 编码序列
	'''
	sum_length = 26		# 字符累计频率，初始为26
	cha = char.copy()

	char_list.append(char.copy())		# 将初始概率空间添加进序列

	i = 0
	for s in strList:	# 根据字符序列中字符出现顺序不断更改概率空间
		p = Decimal(cha.get(s)[1] - cha.get(s)[0])	# 求概率
		char_frequence[s] += 1		# 字符频率增加
		sum_length += 1

		if i == (len(strList) - 1):	# 遍历到最后一个跳出
			# print(s)
			break
		front = cha.get(s)[0]
		for key in char:
			# 概率空间重新分配关键步骤
			cha[key] = [front, front + p * Decimal(char_frequence[key] / sum_length)]
			front += p * Decimal(char_frequence[key] / sum_length)
		i += 1	

		char_list.append(cha.copy())	# 将更改后的概率空间添加进序列

	# 计算编码区间跨度，求码长
	interval = char_list[-1].get(strList[-1])[1] - char_list[-1].get(strList[-1])[0]

	# 选择编码概率
	encode_prob = interval * Decimal(0.9) + char_list[-1].get(strList[-1])[0]	
	print("编码概率：", encode_prob)	

	# 计算码长
	code_length = math.ceil(math.log2(Decimal(1) / interval))
	# print("码长:", code_length)

	bins = float2bin(encode_prob, code_length)

	return code_length, bins
	
	


def adaptive_AC_decode(bins, char_list):
	'''
	自适应模式算数解码
	bins:编码序列
	char_list:编码过程中概率空间的变化序列
	return: 源码
	'''
	num = bin2float(bins)		# 将编码序列转换为概率

	decode_char_list = []		# 解码字符序列
	# 解码
	for char in char_list:	# 遍历概率空间序列
		for key in char:
			if num >= char[key][0] and num <= char[key][1]:
				# print(key)
				decode_char_list.append(key)
	# print(len(char_list))
	decode_chars = "".join(decode_char_list)
	# print(decode_chars)
	return decode_chars

def init():
	char = {}
	char_frequence = {}
	chars = "abcdefghijklmnopqrstuvwxyz"
	for i in range(len(chars)):
		char[chars[i]] = [Decimal(i) * Decimal(1 / 26), Decimal(i + 1) * Decimal(1 / 26)]
		char_frequence[chars[i]] = 1
	return char, char_frequence



if __name__ == '__main__':
	strList = input("请输入字符序列:").lower()
	print('字符序列长度:', len(strList))
	# 根据源码长度动态调整浮点位数
	if len(strList) <=15:
		getcontext().prec = math.ceil(len(strList) * 5)
	else:
		getcontext().prec = math.ceil(len(strList) * 1.7)
	
	char, char_frequence = init()

	char_list = []		# 编码过程中概率空间的变化序列
	code_length, bins = adaptive_AC_encode(strList, char, char_frequence, char_list)
	print('码长:',code_length)
	bins_new = [str(x) for x in bins]
	print('编码结果: ' + "".join(bins_new))
	decode_chars = adaptive_AC_decode(bins, char_list)
	print('解码结果: ' + decode_chars)
