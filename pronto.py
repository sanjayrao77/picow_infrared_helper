#!/usr/bin/python3

# frequency: 1000000/(N*.241246)

codes={}
codes['volumeup_nad']='0000 006b 0023 0002 0120 0812 014c 00ad 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 05d1 014c 0056 0015 0e69'

codes['volumedown_nad']='0000 006b 0023 0002 0120 0817 015a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 05d1 015a 0056 0015 0e69'

codes['mute_nad']='0000 006b 0023 0002 0120 081e 015a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0040 0015 0015 0015 05d0 015a 0056 0015 0e69'

codes['power_nad']='0000 006b 0023 0002 0128 080d 015a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 05d1 015a 0056 0015 0e69'

codes['sleep_nad']='0000 006b 0023 0002 0122 08c4 015c 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d1 015c 0056 0015 0e69'

codes['late_nad']='0000 006b 0023 0002 0119 09e8 0151 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d0 0151 0056 0015 0e69'

codes['left_nad']='0000 006b 0023 0002 0119 09c4 014a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d1 014a 0056 0015 0e69'

codes['right_nad']='0000 006b 0023 0002 0119 09cb 0158 00ad 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d1 0158 0056 0015 0e69'

codes['up_nad']='0000 006b 0023 0002 0119 09bb 015a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d1 015a 0056 0015 0e69'

codes['down_nad']='0000 006b 0023 0002 0119 09bf 015a 00ad 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0015 0015 0040 0015 0040 0015 05d1 015a 0056 0015 0e69'

codes['enter_nad']='0000 006B 0000 0025 0000 09F8 0016 00AC 0016 0040 0016 0040 0016 0040 0016 0016 0016 0016 0016 0016 0016 0016 0016 0040 0016 0016 0016 0016 0016 0040 0016 0040 0016 0040 0016 0040 0016 0040 0016 0016 0016 0016 0016 0040 0016 0016 0016 0016 0016 0040 0016 0040 0016 0016 0016 0016 0016 0040 0016 0016 0016 0040 0016 0040 0016 0016 0016 0016 0016 0040 0016 0040 0016 0310 0016 0056 0016 12FE'

codes['speakera_nad']='0000 006b 0023 0002 0124 0827 015a 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0015 0015 05d0 015a 0056 0015 0e69'

codes['speakerb_nad']='0000 006b 0023 0002 0122 082c 0148 00ac 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0040 0015 0040 0015 0040 0015 0040 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0015 0015 0015 0015 0015 0015 0040 0015 0040 0015 0015 0015 0015 0015 05d0 0148 0056 0015 0e69'

name='speakerb_nad'
str=codes[name]


words=str.split(' ')
if len(words)<5: raise ValueError
tick=int(words[1],16)*0.241246
# print('frequency: %s'%(1000000/tick))

print('static int %s_ircode[]={'%(name),end='')

for idx in range(4,len(words)):
	v=int(words[idx],16)
	print('%d,'%(v*tick),end='')
print('0};')
	