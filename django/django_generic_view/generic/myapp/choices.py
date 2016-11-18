# -*- coding: utf-8 -*-
ACCOUNT_TYPE_CHOICE=(
	('Credit','Credit'),
	('Loan','Loan'),
	('Housing','Housing'),
)
###
ROLES_CHOICE = (
    ('collector', 'Collector'),
    ('supervisor', 'Superviosor'),
)

AGREEMENT_STATUS_CHOICE=(
	('PD', 'Past due'),
	('NPL', 'NPL'),
	('WO','WO')
)
REASON_CODE_CHOICE=(
	('PD', 'Past due'),
	('OC', 'Over credit'),
	('OP','Over and past due')
)
CYCLE_CODE_CHOICE=(
	('1', '1-10'),
	('2', '11')
)
STATE_CODE_CHOICE=(
	('1', 'ลูกหนี้ขออนุมัติดำเนินคดี'),
	('2', 'ลูกหนี้ส่งดำเนินคดี'),
	('3', 'ลูกหนี้มีคำพิภากษา')
)
BLOCK_CODE_CHOICE=(
	('D', 'เสียชีวิต'),
	('B', 'ล้มละลาย'),
	('L', 'ส่งดำเนินคดี'),
	('R', 'ส่งคืนเรียกคืน')
)
ADDRESS_TYPE_CHOICE=(
	('12120','12120'),
)
ZIP_CODE_CHOICE=(
	('12120','12120'),
)