extern "C" {
#include <ntddk.h>
}
#include "crypto_base64.hpp"

/* ʹ��ʾ�� */
VOID Test_Base64() {
	ANSI_STRING str;
	RtlInitAnsiString(&str, "abc test ���� 123456");
	DbgPrint("����(input):%Z \r\n", &str);

	ANSI_STRING cipher = { 0 };
	base64::Encode(&cipher, &str);
	DbgPrint("�����(Encode):%Z \r\n", &cipher);

	ANSI_STRING decode = { 0 };
	base64::Decode(&decode, &cipher);
	DbgPrint("������(Decode):%Z \r\n", &decode);

	ExFreePool_(cipher.Buffer);
	ExFreePool_(decode.Buffer);
}

NTSTATUS DriverUnload(IN struct _DRIVER_OBJECT *pDri) {
	return STATUS_SUCCESS;
}

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT pDri, PUNICODE_STRING regPath) {
	NTSTATUS status = STATUS_SUCCESS;
	pDri->DriverUnload = (PDRIVER_UNLOAD)DriverUnload;

	Test_Base64();

	return status;
}
