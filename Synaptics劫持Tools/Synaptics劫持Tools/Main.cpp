#include <iostream>
#include <Windows.h>
#include <sddl.h>

using namespace std;

bool IsRunAsAdmin() {
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup)) {
        dwError = GetLastError();
    }
    else {
        if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin)) {
            dwError = GetLastError();
        }
        FreeSid(pAdministratorsGroup);
    }


    return (fIsRunAsAdmin == TRUE);
}

static void COLOR_PRINT(const char* s, int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
    printf(s);
    printf("\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}


int main() {
    if (!IsRunAsAdmin()) {
        COLOR_PRINT("[-]���Թ���Ա������иó���",6);
        system("pause");
        return 1;
    }
    HKEY hKey;
    LONG result;
    // �򿪻򴴽����� HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\Synaptics.exe
    result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Synaptics.exe", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    if (result == ERROR_SUCCESS) {
        // �����ַ���ֵ Debugger
        LPCSTR debuggerValue = "mshta \"javascript:new ActiveXObject('WScript.Shell').popup('���ĵ����Ѿ���Synaptics��没�������������ػ��޲�ɱ���ⲻ����Ц����',7,'����',64);window.close();\"";
        result = RegSetValueEx(hKey, L"Debugger", 0, REG_SZ, (BYTE*)debuggerValue, strlen(debuggerValue) + 1);
        if (result == ERROR_SUCCESS) {

            COLOR_PRINT("[+]ע���д��ɹ���",6);
            Sleep(2000);
            COLOR_PRINT("[+]ϵͳӦ��д��ɹ���",6);
            Sleep(1210);
            COLOR_PRINT("[+]���ж���д��ɹ������ڿ��Թرճ����ˡ�",6);
            COLOR_PRINT("By BiliBili-SYSTEM-WINXP-ZDY",6);
        }
        else {
            COLOR_PRINT("[-]ע���д��ʧ�ܣ�",6);
        }
        RegCloseKey(hKey);
    }
    else {
        COLOR_PRINT("[-]�޷�����ע����", 6);
    }

    system("pause");
    return 0;
}
