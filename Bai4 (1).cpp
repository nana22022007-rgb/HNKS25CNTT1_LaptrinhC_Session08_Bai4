#include <stdio.h>
#include <string.h>

struct Subscription {
    int user_id;
    char account_name[31];
    int plan_type;
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;
};

int main() {
    struct Subscription subs[50];
    int n, i;
    int count_downgraded = 0;
    int count_violation = 0;

    printf("Nhap so luong tai khoan (toi da 50): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 50) {
        printf("So luong khong hop le!\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma dinh danh tai khoan (User ID): ");
        scanf("%d", &subs[i].user_id);
        printf("Ten tai khoan / Email (toi da 30 ky tu): ");
        scanf("%30s", subs[i].account_name);
        printf("Hang goi dich vu (1: Free, 2: Individual, 3: Family): ");
        scanf("%d", &subs[i].plan_type);
        printf("So thiet bi dang ket noi: ");
        scanf("%d", &subs[i].active_devices);
        printf("So ngay cham thanh toan cuoc: ");
        scanf("%d", &subs[i].days_overdue);

        subs[i].account_status = 1;

        if (subs[i].plan_type == 1 || subs[i].plan_type == 2) {
            subs[i].max_devices = 1;
        } else if (subs[i].plan_type == 3) {
            subs[i].max_devices = 5;
        } else {
            subs[i].max_devices = 1;
        }
    }

    for (i = 0; i < n; i++) {
        if (subs[i].days_overdue > 3) {
            subs[i].plan_type = 1;
            subs[i].max_devices = 1;
            subs[i].account_status = 0;
            count_downgraded++;
        }
    }

    for (i = 0; i < n; i++) {
        if (subs[i].active_devices > subs[i].max_devices) {
            count_violation++;
        }
    }

    printf("\n======================================= BANG TONG HOP SAU RA SOAT =======================================\n");
    printf("%-8s | %-20s | %-12s | %-10s | %-8s | %-12s | %-10s\n", 
           "User ID", "Account Name", "Plan", "Devices", "Overdue", "Status", "Violation");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        char plan_str[15];
        if (subs[i].plan_type == 1) {
            strcpy(plan_str, "Free");
        } else if (subs[i].plan_type == 2) {
            strcpy(plan_str, "Individual");
        } else if (subs[i].plan_type == 3) {
            strcpy(plan_str, "Family");
        } else {
            strcpy(plan_str, "Unknown");
        }

        char status_str[15];
        if (subs[i].account_status == 1) {
            strcpy(status_str, "Active");
        } else {
            strcpy(status_str, "Downgraded");
        }

        char viol_str[15];
        if (subs[i].active_devices > subs[i].max_devices) {
            strcpy(viol_str, "Vi Pham");
        } else {
            strcpy(viol_str, "Binh Thuong");
        }

        char dev_str[15];
        sprintf(dev_str, "%d/%d", subs[i].active_devices, subs[i].max_devices);

        printf("%-8d | %-20s | %-12s | %-10s | %-8d | %-12s | %-10s\n",
               subs[i].user_id,
               subs[i].account_name,
               plan_str,
               dev_str,
               subs[i].days_overdue,
               status_str,
               viol_str);
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");

    printf("\n=================================== BAO CAO THONG KE VAN HANH ===================================\n");
    printf("- Tong so tai khoan da ra soat: %d\n", n);
    printf("- So luong tai khoan bi tu dong ha cap ve goi Free: %d\n", count_downgraded);
    printf("- So luong tai khoan dang vi pham vuot qua so thiet bi: %d\n", count_violation);
    printf("===================================================================================================\n");

    return 0;
}
