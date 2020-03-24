/**
    HALL MANAGEMENT SYSTEM

    AUTHORS:
        ASSWAD SARKER NOMAAN
        ID: 160101006

        MST. MONAKKARA BEGUM
        ID: 160101026

    CSE 3RD BATCH, BAUST
**/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
    int meal;
    char mealday[31][7];
    char room[10];
    char roll[20];
    char name[100];
    char dept[30];
    char batch[10];
    char phone[20];
    char district[50];
};

struct setup{
    int hallcharge;
    int days;
    double srvcharge;
    double fuel;
    double fuel_std;
    double meal_b;
    double meal_l;
    double meal_d;
    double mealrate[31][3];
    char mm[10];
    char month[10];
    char year[10];
    char pass[41];
    char hallname[200];
    char hallname_s[200];
};

struct data std,chk,upd;
struct setup set;
char temp[6];
char temp_m[6];

void menu(void);
void add_std(void);
void modify_std(void);
void view_rooms(void);
void meal_edit(void);
void bill_info(void);
void settings(void);
void generate_html(void);


int main()
{
    int i,c;
    char password[41] = "";

    system("color a");

    printf("\n\n\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
        printf("\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
        printf("\t\t:::::::::::::::::::::::                          :::::::::::::::::::::::\n");
        printf("\t\t:::::::::::::::::::::::  HALL MANAGEMENT SYSTEM  :::::::::::::::::::::::\n");
        printf("\t\t:::::::::::::::::::::::                          :::::::::::::::::::::::\n");
        printf("\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
        printf("\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");

    FILE *cfgfile;
    cfgfile = fopen("hms_config.dat", "r");
        fscanf(cfgfile, "%[^\n]", &set.pass);
    fclose(cfgfile);

    for(i=0;set.pass[i];i++)
        set.pass[i] += 15;

    printf("\t\t--> WELCOME TO HALL MANAGEMENT SYSTEM");
    printf("\n\n\t\t-----> Please Enter Your Password: ");
    while(strcmp(password,set.pass) != 0)
        {
            for(i=0;(c=getch()) != '\r';i++)
            {
                if(i == 40 && c != '\b')
                    i--;

                else if(c == '\b' && i != 0)
                {
                    printf("\b \b");
                    i = i-2;
                }
                else if(c != '\b')
                {
                    password[i] = c;
                    printf("*");
                }
                else
                    i--;
            }

            password[i] = '\0';

            if(strcmp(password,set.pass) != 0)
            {
                system("cls");
                system("color c");
                printf("\n\n\n\n\t\tWrong Password! Enter Again: ");
            }
        }


    FILE *setfile;
    setfile = fopen("hms_settings.dat", "r");
        fscanf(setfile, "%s\n%s %s %s %d %d %lf %lf", &set.hallname, &set.year,&set.mm,&set.month,&set.days,&set.hallcharge,&set.srvcharge,&set.fuel);
        for(i=0;i<31;i++)
            fscanf(setfile, "%lf %lf %lf", &set.mealrate[i][0], &set.mealrate[i][1], &set.mealrate[i][2]);
    fclose(setfile);

    strcpy(set.hallname_s,set.hallname);
    for(i=0;i<strlen(set.hallname_s);i++)
    {
        if(set.hallname_s[i] == '#')
            set.hallname_s[i] =' ';
    }

    menu();

    return 0;
}


void menu(void)
{
    int choice;

    system("cls");
    system("color a");
    printf("\t\t\t::::::::::::::::::::::::::::::::\n");
    printf("\t\t\t:::: HALL MANAGEMENT SYSTEM ::::\n");
    printf("\t\t\t::::::::::::::::::::::::::::::::\n\n");

    printf("  %s\t\t\t\tMonth: %s-%s\n\n\n\n",set.hallname_s,set.month,set.year);

    printf("\t\t1 :: Add Student\n");
    printf("\t\t2 :: Modify Student Information\n");
    printf("\t\t3 :: View Room Information\n");
    printf("\t\t4 :: Meal Edit\n");
    printf("\t\t5 :: Bill Information\n");
    printf("\t\t6 :: Settings\n");
    printf("\t\t0 :: Exit\n\n");

    printf("\t\tEnter Choice >> ");
    scanf("%d", &choice);

    system("cls");

    switch(choice)
    {
        case 1:
            add_std();
            break;

        case 2:
            modify_std();
            break;

        case 3:
            view_rooms();
            break;

        case 4:
            meal_edit();
            break;

        case 5:
            bill_info();
            break;

        case 6:
            settings();
            break;

        case 0:
            exit(0);
            break;

        default:
            printf("Wrong Choice.. Please Select Correct One\n");
            getch();
            menu();
            break;
    }
}


void add_std(void)
{
    int i,r_count = 0;
    char again = 'y';
    FILE *data;


    while(again == 'y' || again == 'Y')
    {
        printf("HALL MANAGEMENT SYSTEM >>\tADD STUDENT\n\n");

        do
        {
            data = fopen("hms_data.dat", "r");
                r_count = 0;
                printf("Enter Room No: ");
                scanf("%s", &std.room);
                printf("\tChecking room...  ");

                while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                {
                    for(i=0;i<31;i++)
                        {
                           fscanf(data,"%s", &temp_m);
                        }

                    if(strcmp(std.room,chk.room) == 0)
                    {
                        r_count++;
                        if(r_count == 4)
                            break;
                    }
                }

                if(r_count >= 4)
                {
                    printf("Room %s is Full!!\n", std.room);
                }

                else
                    printf("Free space: %d\n", 4-r_count);
            fclose(data);
        } while(r_count >= 4);

        do
        {
            data = fopen("hms_data.dat", "r");
                printf("Enter Student's ID/Roll: ");
                scanf("%s", &std.roll);
                printf("\tChecking ID...  ");

                while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                {
                    for(i=0;i<31;i++)
                        {
                           fscanf(data,"%s", &temp_m);
                        }

                    if(strcmp(std.roll,chk.roll) == 0)
                    {
                        printf("ID %s already exists in room %s\n", chk.roll,chk.room);
                        break;
                    }
                }
            fclose(data);
        } while(strcmp(std.roll,chk.roll) == 0);

        printf("OK\n");

        printf("Enter Student Name: ");
        scanf(" %[^\n]", &std.name);

        printf("Enter Department: ");
        scanf(" %[^\n]", &std.dept);

        printf("Enter Batch: ");
        scanf(" %[^\n]", &std.batch);

        printf("Enter Phone no: ");
        scanf(" %[^\n]", &std.phone);

        printf("Enter Home District: ");
        scanf(" %[^\n]", &std.district);

        for(i=0;i<strlen(std.name);i++)
        {
            if(std.name[i] == ' ')
                std.name[i] ='#';
        }

        data = fopen("hms_data.dat", "a");
            fprintf(data,"%s %s %s %s %s %s %s meals: ", std.room, std.roll, std.name, std.dept, std.batch, std.phone, std.district);
            for(i=1000;i<=31000;i=i+1000)
            {
                if(i<10000)
                    fprintf(data,"0%d ", i);
                else
                    fprintf(data,"%d ", i);
            }
            fprintf(data,"\n");
        fclose(data);

        printf("\nAdd Success!!!!!!!!\nDo you want to add more? (y/n) >> ");
        scanf(" %c", &again);
        system("cls");
    }

    system("cls");

    menu();
}


void modify_std(void)
{
    FILE *data,*new_data;
    int i,j,choice,confirm,flag=0;

    printf("HALL MANAGEMENT SYSTEM >>\tMODIFY STUDENT INFORMATION\n\n");

    printf("Enter Student ID/Roll: ");
    scanf("%s", &std.roll);
    printf("\tSearching ID...  ");

    data = fopen("hms_data.dat","r");
        while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
        {
            for(j=0;j<31;j++)
            {
               fscanf(data,"%s", &chk.mealday[j]);
            }

            if(strcmp(std.roll,chk.roll) == 0)
            {
                flag = 1;
                for(i=0;i<strlen(chk.name);i++)
                {
                    if(chk.name[i] == '#')
                    chk.name[i] =' ';
                }

                printf("Found!!\n\nStudent Information:\n");
                printf("\tRoom No           :  %s\n", chk.room);
                printf("\tID No             :  %s\n", chk.roll);
                printf("\tName              :  %s\n", chk.name);
                printf("\tDepartment        :  %s\n", chk.dept);
                printf("\tBatch             :  %s\n", chk.batch);
                printf("\tPhone No          :  %s\n", chk.phone);
                printf("\tHome District     :  %s\n", chk.district);
                break;
            }
        }
    fclose(data);

    if(flag == 1)
    {
        printf("\nType '1' to Edit :: '2' to Delete :: '0' to Go Back >> ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("\n\nEnter new Data: \n");
            printf("\tRoom No               :  %s\n", chk.room);

            printf("\tStudent Roll/ID       :  ");
            scanf("%s", &upd.roll);

            printf("\tEnter Student Name    :  ");
            scanf(" %[^\n]", &upd.name);

            printf("\tEnter Department      :  ");
            scanf("%s", &upd.dept);

            printf("\tEnter Batch           :  ");
            scanf("%s", &upd.batch);

            printf("\tEnter Phone No.       :  ");
            scanf("%s", &upd.phone);

            printf("\tEnter Home District   :  ");
            scanf("%s", &upd.district);

            for(i=0;i<strlen(upd.name);i++)
            {
                if(upd.name[i] == ' ')
                    upd.name[i] ='#';
            }

            data = fopen("hms_data.dat","r");
            new_data = fopen("hms_data.tmp","w");
                while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                {
                    for(j=0;j<31;j++)
                    {
                       fscanf(data,"%s", &chk.mealday[j]);
                    }

                    if(strcmp(std.roll,chk.roll) == 0)
                        {
                            fprintf(new_data,"%s %s %s %s %s %s %s %s ", chk.room,upd.roll,upd.name,upd.dept,upd.batch,upd.phone,upd.district,temp);
                            for(j=0;j<31;j++)
                            {
                                fprintf(new_data,"%s ", chk.mealday[j]);
                            }
                            fprintf(new_data,"\n");
                        }
                    else
                    {
                        fprintf(new_data,"%s %s %s %s %s %s %s %s ", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district,temp);
                        for(j=0;j<31;j++)
                            {
                                    fprintf(new_data,"%s ", chk.mealday[j]);
                            }
                            fprintf(new_data,"\n");
                    }
                }
            fclose(data);
            fclose(new_data);
            remove("hms_data.dat");
            rename("hms_data.tmp","hms_data.dat");
            printf("Done!\n");
        }

        else if(choice == 2)
        {
            printf("\n\t1: Confirm Delete || 0: Cancel >> ");
            scanf("%d", &confirm);

            if(confirm == 1)
            {
                data = fopen("hms_data.dat","r");
                new_data = fopen("hms_data.tmp","w");
                    while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                    {
                        for(j=0;j<31;j++)
                        {
                           fscanf(data,"%s", &chk.mealday[j]);
                        }
                        if(strcmp(std.roll,chk.roll) == 0)
                            printf("Deleting Record..\n");
                        else
                        {
                            fprintf(new_data,"%s %s %s %s %s %s %s %s ", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district,temp);
                            for(j=0;j<31;j++)
                            {
                                    fprintf(new_data,"%s ", chk.mealday[j]);
                            }
                            fprintf(new_data,"\n");
                        }
                    }
                fclose(data);
                fclose(new_data);
                remove("hms_data.dat");
                rename("hms_data.tmp","hms_data.dat");
                printf("Done!\n");
            }
        }

        else if(choice == 0)
                menu();

        else
            printf("Wrong choice!!\n");
    }

    else
        printf("Not Found!\n");

    printf("Press any key to go back.");
    getch();
    system("cls");
    menu();
}


void view_rooms(void)
{
    FILE *data;
    char again= 'a';
    int i,j,page=1,flag;
    char search_rm[10];

    printf("HALL MANAGEMENT SYSTEM >>\tVIEW ROOM INFORMATION\n\n");

    printf("Enter 'A' to view all rooms or Enter Room Number: ");
    scanf("%s", &search_rm);

    data = fopen("hms_data.dat","r");
        if(strcmp(search_rm,"A") == 0 || strcmp(search_rm,"a") == 0)
        {
            flag = 0;
            while(again != 27)
            {
                system("cls");
                printf("Showing Result: (Page %d)\n\n", page);
                printf("\tPress any key to go to next page or 'Esc' to go back\n");
                printf("\n\nRoom    Roll          Name                        Dept.   Batch   Phone          Home District\n");

                for(i=0;i<20;i++)
                {
                    if(fscanf(data,"%s %s %s %s %s %s %s %s", &std.room,&std.roll,&std.name,&std.dept,&std.batch,&std.phone,&std.district,&temp) != EOF)
                    {
                        for(j=0;j<31;j++)
                        {
                           fscanf(data,"%s", &temp_m);
                        }

                        for(j=0;j<strlen(std.name);j++)
                        {
                            if(std.name[j] == '#')
                                std.name[j] = ' ';
                        }
                        printf("%-7s %-13s %-27s %-7s %-7s %-14s %s\n", std.room,std.roll,std.name,std.dept,std.batch,std.phone,std.district);
                    }

                    else
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag == 1)
                {
                    printf("\nAll records loaded. Press any key to go back..\n");
                    getch();
                    break;
                }

                else
                    {
                        again = getch();
                        page++;
                    }
            }
        }

        else
        {
            flag = 0;
            printf("\n\nRoom    Roll          Name                        Dept.   Batch   Phone          Home District\n");

            while(fscanf(data,"%s %s %s %s %s %s %s %s", &std.room,&std.roll,&std.name,&std.dept,&std.batch,&std.phone,&std.district,&temp) != EOF)
            {
                for(j=0;j<31;j++)
                        {
                           fscanf(data,"%s", &temp_m);
                        }

                for(j=0;j<strlen(std.name);j++)
                {
                    if(std.name[j] == '#')
                        std.name[j] = ' ';
                }
                if(strcmp(search_rm,std.room) == 0)
                    {
                        flag = 1;
                        printf("%-7s %-13s %-27s %-7s %-7s %-14s %s\n", std.room,std.roll,std.name,std.dept,std.batch,std.phone,std.district);
                    }
            }
            if(flag == 1)
                printf("\n  All records loaded. Press any key to go back..\n");

            else
                printf("\n  Not Found!! Press any key to go back..\n");

            getch();
        }
    fclose(data);
    system("cls");

    menu();
}


void meal_edit(void)
{
    FILE *data,*new_data;
    int i,j,check,flag=0,r_count=0,CountDay = 0, CountMeals = 0, start_date, end_date, cancel = 0;
    char meal_temp[6];

    printf("HALL MANAGEMENT SYSTEM >>\tMEAL ON / OFF\n\n");

    printf("Enter Student's ID/Roll: ");
    scanf("%s", &std.roll);
    printf("\tSearching ID...  ");

    data = fopen("hms_data.dat","r");
        while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
        {
            for(j=0;j<31;j++)
            {
                fscanf(data,"%s", &chk.mealday[j]);
                strcpy(upd.mealday[j], chk.mealday[j]);
            }

            if(strcmp(std.roll,chk.roll) == 0)
            {
                for(j=0;j<set.days;j++)
                {
                    if(chk.mealday[j][2] == '1')
                        CountMeals++;

                    if(chk.mealday[j][3] == '1')
                        CountMeals++;

                    if(chk.mealday[j][4] == '1')
                        CountMeals++;

                    if(chk.mealday[j][2] == '1' || chk.mealday[j][3] == '1' || chk.mealday[j][4] == '1')
                        CountDay++;
                }

                flag = 1;
                for(i=0;i<strlen(chk.name);i++)
                {
                    if(chk.name[i] == '#')
                        chk.name[i] =' ';
                }

                printf("Found!!\n\nStudent Information:\n");
                printf("\tRoom No           :  %s\n", chk.room);
                printf("\tID No             :  %s\n", chk.roll);
                printf("\tName              :  %s\n", chk.name);
                printf("\tDepartment        :  %s\n", chk.dept);
                printf("\tBatch             :  %s\n", chk.batch);
                printf("\tPhone No          :  %s\n", chk.phone);
                printf("\tHome District     :  %s\n\n", chk.district);
                printf("\tMeal Days         :  %d (%d Meals)", CountDay, CountMeals);
                printf("  [Month: %s-%s]\n", set.month,set.year);

                printf("\n\n MEAL INFORMATION OF ID %s", std.roll);
                printf("\n\n Total Meals: %d (%d Days)\n\n", CountMeals, CountDay);

                printf(" Day ::::  B     L     D\n");
                for(i=0;i<set.days;i++)
                    printf("%3d  :::: %3s %5s %5s\n", i+1, chk.mealday[i][2]=='1'?"ON":"-",chk.mealday[i][3]=='1'?"ON":"-",chk.mealday[i][4]=='1'?"ON":"-");
                break;
            }
        }
    fclose(data);

    if(flag == 1)
    {
        printf("\n\t1 : Add/Edit Meal(s) || 0 : Cancel >> ");
        scanf("%d", &check);

        switch(check)
        {
        case 1:
            printf("\n\nEnter New Meal: \n");
            printf("\nEnter Start Date: ");
            scanf("%d", &start_date);
            if(start_date < 1 || start_date > set.days)
            {
                printf("Invalid Start Date\nPress any key..");
                getch();
                break;
            }
            printf("\nEnter End Date: ");
            scanf("%d", &end_date);
            if(start_date > set.days || end_date > set.days || end_date < start_date)
            {
                printf("Invalid End Date\n");
                break;
            }
            for(i=start_date;i<=end_date;i++)
            {
                printf("Day %2d: ", i);
                fflush(stdin);
                gets(meal_temp);
                if(meal_temp[0] == 'x' || meal_temp[0] == 'X' || meal_temp[1] == 'x' || meal_temp[1] == 'X' || meal_temp[2] == 'x' || meal_temp[2] == 'X')
                    break;

                while( (meal_temp[0] < '0' || meal_temp[0] > '1' || meal_temp[1] < '0' || meal_temp[1] > '1' || meal_temp[2] < '0' || meal_temp[2] > '1') )
                {
                    printf("\nEnter Again\n");
                    printf("Day %2d: ", i);
                    gets(meal_temp);

                    if(meal_temp[0] == 'x' || meal_temp[0] == 'X' || meal_temp[1] == 'x' || meal_temp[1] == 'X' || meal_temp[2] == 'x' || meal_temp[2] == 'X')
                    {
                        cancel = 1;
                        break;
                    }
                }
                if(cancel == 1)
                    break;

                upd.mealday[i-1][2] = (meal_temp[0]=='1'?'1':'0');
                upd.mealday[i-1][3] = (meal_temp[1]=='1'?'1':'0');
                upd.mealday[i-1][4] = (meal_temp[2]=='1'?'1':'0');
            }

            for(i=0;i<strlen(std.name);i++)
            {
                if(std.name[i] == ' ')
                    std.name[i] ='#';
            }
            data = fopen("hms_data.dat","r");
            new_data = fopen("hms_data.tmp","w");
                while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                {
                    for(j=0;j<31;j++)
                        {
                           fscanf(data,"%s", &chk.mealday[j]);

                        }
                    if(strcmp(std.roll,chk.roll) == 0)
                    {
                        //fprintf(new_data,"%s %s %s %s %s %s %s %d\n", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district,std.meal);

                        fprintf(new_data,"%s %s %s %s %s %s %s %s ", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district,temp);
                        for(j=0;j<31;j++)
                        {
                            fprintf(new_data,"%s ", upd.mealday[j]);
                        }
                        fprintf(new_data,"\n");
                    }

                    else
                    {
                        fprintf(new_data,"%s %s %s %s %s %s %s %s ", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district,temp);
                        for(j=0;j<31;j++)
                        {
                            fprintf(new_data,"%s ", chk.mealday[j]);
                        }
                        fprintf(new_data,"\n");
                    }
                }
            fclose(data);
            fclose(new_data);
            remove("hms_data.dat");
            rename("hms_data.tmp","hms_data.dat");
            printf("Done!\n");
            break;

        default:
            menu();
            break;
        }

    }

    else
        printf("Not Found!\n");

    printf("\nPress any key to go back.");
    getch();
    system("cls");
    menu();
}


void bill_info(void)
{
    system("cls");

    FILE *data;
    char again= 'a', search_rm[10];
    int i,j,page=1,flag=0, choice, CountDay = 0, CountMeals = 0;
    double meal_charge, bill_srvcharge,bill_total,bill_meal;

    //meal_charge = set.meal_b + set.meal_l + set.meal_d;
    for(j=0;j<set.days;j++)
            meal_charge += set.mealrate[j][0] + set.mealrate[j][1] + set.mealrate[j][2];

    printf("HALL MANAGEMENT SYSTEM >>\tBILL INFORMATION\n\n");


    printf("\t\t1 :: Show All Bills\n");
    printf("\t\t2 :: Show Bill By ID\n");
    printf("\t\t3 :: Show Bills By Room\n");
    printf("\t\t4 :: Generate HTML\n");
    printf("\t\t0 :: Back\n");

    printf("\t\tEnter Choice >> ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        system("cls");
        flag = 0;
        data = fopen("hms_data.dat","r");
            while(again != 27)
            {
                system("cls");
                printf("Showing Result: (Page %d)\n\n", page);
                printf("\tPress any key to go to next page or 'Esc' to go back\n");
                printf("\n\nRoom    Roll          Name                        Dept.   Batch   Meals   Meal Charge   Service Charge   Fuel & Spices   Hall Charge   Total\n");

                for(i=0;i<20;i++)
                {
                    if(fscanf(data,"%s %s %s %s %s %s %s %s", &std.room,&std.roll,&std.name,&std.dept,&std.batch,&std.phone,&std.district,&temp) != EOF)
                    {
                        CountMeals = 0;
                        CountDay = 0;

                        for(j=0;j<31;j++)
                            {
                               fscanf(data,"%s", &chk.mealday[j]);
                            }

                        for(j=0;j<set.days;j++)
                        {
                            if(chk.mealday[j][2] == '1')
                                CountMeals++;

                            if(chk.mealday[j][3] == '1')
                                CountMeals++;

                            if(chk.mealday[j][4] == '1')
                                CountMeals++;

                            if(chk.mealday[j][2] == '1' || chk.mealday[j][3] == '1' || chk.mealday[j][4] == '1')
                                CountDay++;
                        }

                        for(j=0;j<strlen(std.name);j++)
                        {
                            if(std.name[j] == '#')
                                std.name[j] = ' ';
                        }

                        if(CountDay == 0)
                            set.fuel_std = 0;
                        else
                            set.fuel_std = set.fuel;

                        /*bill_meal = (set.meal_b + set.meal_l + set.meal_d) * std.meal;
                        bill_srvcharge = bill_meal * (set.srvcharge/100);
                        bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;*/

                        bill_meal = 0;
                        for(j=0;j<set.days;j++)
                        {
                            bill_meal += (chk.mealday[j][2]=='1'?set.mealrate[j][0]:0) + (chk.mealday[j][3]=='1'?set.mealrate[j][1]:0) + (chk.mealday[j][4]=='1'?set.mealrate[j][2]:0);
                        }

                        bill_srvcharge = bill_meal * (set.srvcharge/100);
                        bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;

                        printf("%-7s %-13s %-27s %-7s %-7s %-7d %-13.2lf %-16.2lf %-15.2lf %-13d %.2lf\n", std.room, std.roll, std.name, std.dept, std.batch, CountMeals, bill_meal, bill_srvcharge, set.fuel_std, set.hallcharge, bill_total);
                    }

                    else
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag == 1)
                {
                    printf("\nAll records loaded. Press any key to go back..\n");
                    getch();
                    break;
                }

                else
                    {
                        again = getch();
                        page++;
                    }
            }
        fclose(data);
        bill_info();
    }

    else if(choice == 2)
    {
        system("cls");
        printf("Enter Student's ID/Roll: ");
        scanf("%s", &std.roll);
        printf("\tSearching ID...  ");

        data = fopen("hms_data.dat","r");
            while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
            {
                CountMeals = 0;
                CountDay = 0;

                for(j=0;j<31;j++)
                    {
                       fscanf(data,"%s", &chk.mealday[j]);
                    }

                for(j=0;j<set.days;j++)
                {
                    if(chk.mealday[j][2] == '1')
                        CountMeals++;

                    if(chk.mealday[j][3] == '1')
                        CountMeals++;

                    if(chk.mealday[j][4] == '1')
                        CountMeals++;

                    if(chk.mealday[j][2] == '1' || chk.mealday[j][3] == '1' || chk.mealday[j][4] == '1')
                        CountDay++;
                }

                if(strcmp(std.roll,chk.roll) == 0)
                {
                    flag = 1;

                    if(CountDay == 0)
                        set.fuel_std = 0;
                    else
                        set.fuel_std = set.fuel;

                    /*bill_meal = (set.meal_b + set.meal_l + set.meal_d) * chk.meal;
                    bill_srvcharge = bill_meal * (set.srvcharge/100);
                    bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;*/

                    bill_meal = 0;
                    for(j=0;j<set.days;j++)
                    {
                        bill_meal += (chk.mealday[j][2]=='1'?set.mealrate[j][0]:0) + (chk.mealday[j][3]=='1'?set.mealrate[j][1]:0) + (chk.mealday[j][4]=='1'?set.mealrate[j][2]:0);
                    }

                    bill_srvcharge = bill_meal * (set.srvcharge/100);
                    bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;

                    for(i=0;i<strlen(chk.name);i++)
                    {
                        if(chk.name[i] == '#')
                            chk.name[i] =' ';
                    }

                    printf("Found!!\n\nStudent Information:\n");
                    printf("\tRoom No           :  %s\n", chk.room);
                    printf("\tID No             :  %s\n", chk.roll);
                    printf("\tName              :  %s\n", chk.name);
                    printf("\tDepartment        :  %s\n", chk.dept);
                    printf("\tBatch             :  %s\n", chk.batch);
                    printf("\tPhone No          :  %s\n", chk.phone);
                    printf("\tHome District     :  %s\n\n", chk.district);
                    printf("\tMeal Days         :  %d", CountDay);
                    printf("  (Month: %s-%s)\n\n", set.month,set.year);

                    printf("Bill Information:\n");
                    printf("\tTotal Meals       : %d\n", CountMeals);
                    printf("\tMeal Charge       : %.2lf TK\n", bill_meal);
                    printf("\tService Charge    : %.2lf TK\n", bill_srvcharge);
                    printf("\tFuel & Spices     : %.2lf TK\n", set.fuel_std);
                    printf("\tHall Charge       : %d TK\n", set.hallcharge);
                    printf("\tTotal             : %.2lf TK\n", bill_total);

                    break;
                }
            }
        fclose(data);
        printf("\nDone. Press any key to go back\n");
        getch();
        bill_info();
    }

    else if(choice == 3)
    {
        system("cls");
        flag = 0;

        printf("Enter Room: ");
        scanf("%s", &search_rm);
        printf("\n\nRoom    Roll          Name                        Dept.   Batch   Meals   Meal Charge   Service Charge   Fuel & Spices   Hall Charge   Total\n");

        data = fopen("hms_data.dat","r");
            while(fscanf(data,"%s %s %s %s %s %s %s %s", &std.room,&std.roll,&std.name,&std.dept,&std.batch,&std.phone,&std.district,&temp) != EOF)
            {
                CountMeals = 0;
                CountDay = 0;

                for(j=0;j<31;j++)
                    {
                       fscanf(data,"%s", &chk.mealday[j]);
                    }

                for(j=0;j<set.days;j++)
                {
                    if(chk.mealday[j][2] == '1')
                        CountMeals++;

                    if(chk.mealday[j][3] == '1')
                        CountMeals++;

                    if(chk.mealday[j][4] == '1')
                        CountMeals++;

                    if(chk.mealday[j][2] == '1' || chk.mealday[j][3] == '1' || chk.mealday[j][4] == '1')
                        CountDay++;
                }

                if(strcmp(search_rm,std.room) == 0)
                {
                    flag = 1;
                    for(j=0;j<strlen(std.name);j++)
                    {
                        if(std.name[j] == '#')
                            std.name[j] = ' ';
                    }

                    if(CountDay == 0)
                        set.fuel_std = 0;
                    else
                        set.fuel_std = set.fuel;

                    /*bill_meal = (set.meal_b + set.meal_l + set.meal_d) * std.meal;
                    bill_srvcharge = bill_meal * (set.srvcharge/100);
                    bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;*/

                    bill_meal = 0;
                    for(j=0;j<set.days;j++)
                    {
                        bill_meal += (chk.mealday[j][2]=='1'?set.mealrate[j][0]:0) + (chk.mealday[j][3]=='1'?set.mealrate[j][1]:0) + (chk.mealday[j][4]=='1'?set.mealrate[j][2]:0);
                    }

                    bill_srvcharge = bill_meal * (set.srvcharge/100);
                    bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;

                    printf("%-7s %-13s %-27s %-7s %-7s %-7d %-13.2lf %-16.2lf %-15.2lf %-13d %.2lf\n", std.room, std.roll, std.name, std.dept, std.batch, CountMeals, bill_meal, bill_srvcharge, set.fuel_std, set.hallcharge, bill_total);
                }
            }


            if(flag == 1)
                printf("\nAll records loaded. Press any key to go back..\n");
            else
                printf("\n  Not Found!! Press any key to go back..\n");

            getch();
        fclose(data);
        bill_info();
    }


    else if(choice == 4)
    {
        system("cls");
        generate_html();
        bill_info();
    }

    else if(choice == 0)
        menu();

    else
        system("cls");
        printf("Wrong Choice.\nPress any key to go back.. ");
        getch();
        bill_info();
}


void settings(void)
{
    int i,c,choice,new_hallcharge,new_days,mm_month,start_date,end_date;
    double new_srvcharge, new_fuel,new_meal_b,new_meal_l,new_meal_d;
    char confirm,new_month[10],new_year[10], back_file[100] = "backup\\", back_settings[100] = "", oldpass[41], newpass[41]="1", renewpass[41]="2";
    FILE *setfile, *setback, *data, *new_data, *cfgfile;

    system("cls");

    setfile = fopen("hms_settings.dat", "r");
        fscanf(setfile, "%s\n%s %s %s %d %d %lf %lf", &set.hallname, &set.year,&set.mm,&set.month,&set.days,&set.hallcharge,&set.srvcharge,&set.fuel);
        for(i=0;i<31;i++)
            fscanf(setfile, "%lf %lf %lf", &set.mealrate[i][0], &set.mealrate[i][1], &set.mealrate[i][2]);
    fclose(setfile);

    strcpy(set.hallname_s,set.hallname);
    for(i=0;i<strlen(set.hallname_s);i++)
    {
        if(set.hallname_s[i] == '#')
        set.hallname_s[i] =' ';
    }

    printf("\n\n SETTINGS\n");
        printf("\t\t1 :: Hall Name (%s)\n", set.hallname_s);
        printf("\t\t2 :: Month (%s-%s)\n", set.month, set.year);
        printf("\t\t3 :: Hall Charge (%d TK)\n", set.hallcharge);
        printf("\t\t4 :: Service Charge (%.2lf%%)\n", set.srvcharge);
        printf("\t\t5 :: Fuel & Spices Charge (%.2lf TK)\n", set.fuel);
        printf("\t\t6 :: Meal Charge\n");
        printf("\t\t7 :: Change Password\n");
        printf("\t\t0 :: Go Back\n\n");

    printf("\t\tEnter Choice >> ");
        scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        system("cls");
        printf("Hall Name: %s\n", set.hallname_s);
        printf("Enter New Hall Name: ");
        scanf(" %[^\n]", &set.hallname);
        for(i=0;i<strlen(set.hallname);i++)
            {
                if(set.hallname[i] == ' ')
                    set.hallname[i] ='#';
            }
        setfile = fopen("hms_settings.dat", "w");
            fprintf(setfile,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname, set.year,set.mm,set.month,set.days,set.hallcharge,set.srvcharge,set.fuel);
            for(i=0;i<31;i++)
                fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        fclose(setfile);
        break;

    case 2:
        system("cls");
        printf("Current Month: %s-%s\n", set.month,set.year);

        printf("Enter Year: ");
        scanf("%s", &new_year);

        printf("Enter Month (MM): ");
        scanf("%d", &mm_month);

        if(mm_month == 1)
            {
                strcpy(new_month,"Jan");
                new_days = 31;
            }
        else if(mm_month == 2)
            {
                printf("Enter Days: ");
                scanf("%d", &new_days);
                strcpy(new_month,"Feb");
            }
        else if(mm_month == 3)
            {
                strcpy(new_month,"Mar");
                new_days = 31;
            }
        else if(mm_month == 4)
            {
                strcpy(new_month,"Apr");
                new_days = 30;
            }
        else if(mm_month == 5)
            {
                strcpy(new_month,"May");
                new_days = 31;
            }
        else if(mm_month == 6)
            {
                strcpy(new_month,"Jun");
                new_days = 30;
            }

        else if(mm_month == 7)
            {
                strcpy(new_month,"Jul");
                new_days = 31;
            }
        else if(mm_month == 8)
            {
                strcpy(new_month,"Aug");
                new_days = 31;
            }
        else if(mm_month == 9)
            {
                strcpy(new_month,"Sep");
                new_days = 30;
            }
        else if(mm_month == 10)
            {
                strcpy(new_month,"Oct");
                new_days = 31;
            }
        else if(mm_month == 11)
            {
                strcpy(new_month,"Nov");
                new_days = 30;
            }
        else if(mm_month == 12)
            {
                strcpy(new_month,"Dec");
                new_days = 31;
            }
        else
        {
            printf("Wrong Format!! Press any key to go back.. ");
            getch();
            break;
        }

        if(strcmp(set.month,new_month) == 0 && strcmp(set.year,new_year) == 0)
            {
                setfile = fopen("hms_settings.dat", "w+");
                    fprintf(setfile,"%s\n%s\n%d %s\n%d\n%d\n%lf\n%lf\n", set.hallname,new_year,mm_month,new_month,new_days,set.hallcharge,set.srvcharge,set.fuel);
                    for(i=0;i<31;i++)
                        fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
                fclose(setfile);
            }

        else
        {
            printf("After changing month, the HTML file will be generated and bills & meals of given month will be reset.\nDo you want to continue? (y/n): " );
            scanf(" %c", &confirm);

            if(confirm == 'y' || confirm == 'Y')
            {
                generate_html();

                data = fopen("hms_data.dat","r");
                new_data = fopen("hms_data.tmp","w");
                    //while(fscanf(data,"%s %s %s %s %s %s %s %d", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &chk.meal) != EOF)
                    while(fscanf(data,"%s %s %s %s %s %s %s %s", &chk.room, &chk.roll, &chk.name, &chk.dept, &chk.batch, &chk.phone, &chk.district, &temp) != EOF)
                    {
                        for(i=0;i<31;i++)
                            {
                               fscanf(data,"%s", &temp_m);
                            }
                        //fprintf(new_data,"%s %s %s %s %s %s %s 0\n", chk.room,chk.roll,chk.name,chk.dept,chk.batch,chk.phone,chk.district);
                        fprintf(new_data,"%s %s %s %s %s %s %s meals: ", chk.room, chk.roll, chk.name, chk.dept, chk.batch, chk.phone, chk.district);
                            for(i=1000;i<=31000;i=i+1000)
                            {
                                if(i<10000)
                                    fprintf(new_data,"0%d ", i);
                                else
                                    fprintf(new_data,"%d ", i);
                            }
                            fprintf(new_data,"\n");
                    }
                fclose(data);
                fclose(new_data);

                strcat(back_file,set.year);
                strcat(back_file,"-");
                strcat(back_file,set.mm);
                strcat(back_settings,back_file);
                strcat(back_settings,"_hms_settings.dat");
                strcat(back_file,"_hms_data.dat");
                mkdir("backup");
                rename("hms_data.dat",back_file);
                rename("hms_data.tmp","hms_data.dat");

                setback = fopen(back_settings, "w");
                    fprintf(setback,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname,set.year,set.mm,set.month,set.days,set.hallcharge,set.srvcharge,set.fuel);
                    for(i=0;i<31;i++)
                        fprintf(setback, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
                fclose(setback);

                setfile = fopen("hms_settings.dat", "w");
                    fprintf(setfile,"%s\n%s\n%d %s\n%d\n%d\n%lf\n%lf\n", set.hallname,new_year,mm_month,new_month,new_days,set.hallcharge,set.srvcharge,set.fuel);
                    for(i=0;i<31;i++)
                        fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
                fclose(setfile);

                printf("Done!!\n\nSet bills for new month if you need.");
                getch();
            }
            else
                printf("Canceled!\n");
        }

        break;

    case 3:
        system("cls");
        printf("Current Hall Charge: %d\n", set.hallcharge);
        printf("Enter New Hall Charge: ");
        scanf("%d", &new_hallcharge);
        setfile = fopen("hms_settings.dat", "w");
            fprintf(setfile,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname,set.year,set.mm,set.month,set.days,new_hallcharge,set.srvcharge,set.fuel);
            for(i=0;i<31;i++)
                fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        fclose(setfile);
        break;

    case 4:
        system("cls");
        printf("Current Service Charge: %.2lf\n", set.srvcharge);
        printf("Enter New Service Charge: ");
        scanf("%lf", &new_srvcharge);
        setfile = fopen("hms_settings.dat", "w");
            fprintf(setfile,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname,set.year,set.mm,set.month,set.days,set.hallcharge,new_srvcharge,set.fuel);
            for(i=0;i<31;i++)
                fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        fclose(setfile);

        break;

    case 5:
        system("cls");
        printf("Current Fuel & Spices Charge: %.2lf\n", set.fuel);
        printf("Enter New Fuel & Spices Charge: ");
        scanf("%lf", &new_fuel);
        setfile = fopen("hms_settings.dat", "w");
            fprintf(setfile,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname, set.year,set.mm,set.month,set.days,set.hallcharge,set.srvcharge,new_fuel);
            for(i=0;i<31;i++)
                fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        fclose(setfile);

        break;

    case 6:
        system("cls");
        printf(" Current Meal Charge:\n Day     Breakfast     Lunch        Dinner\n");
        for(i=0;i<set.days;i++)
            printf("%3d :::: %5.2lf TK     %5.2lf TK     %5.2lf TK\n", i+1, set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        printf("\n\nEnter New Meal Charge: \n");
        printf("\nEnter Start Date: ");
        scanf("%d", &start_date);
        if(start_date < 1 || start_date > set.days)
        {
            printf("Invalid Start Date\nPress any key..");
            getch();
            break;
        }
        printf("\nEnter End Date: ");
        scanf("%d", &end_date);
        if(start_date > set.days || end_date > set.days || end_date < start_date)
        {
            printf("Invalid End Date\nPress any key..", set.days);
            getch();
            break;
        }
        for(i=start_date;i<=end_date;i++)
            {
                printf("Day %2d: ", i);
                scanf("%lf %lf %lf", &set.mealrate[i-1][0], &set.mealrate[i-1][1], &set.mealrate[i-1][2]);
            }
        setfile = fopen("hms_settings.dat", "w+");
            fprintf(setfile,"%s\n%s\n%s %s\n%d\n%d\n%lf\n%lf\n", set.hallname, set.year,set.mm,set.month,set.days,set.hallcharge,set.srvcharge,set.fuel);
            for(i=0;i<31;i++)
                fprintf(setfile, "%lf %lf %lf\n", set.mealrate[i][0], set.mealrate[i][1], set.mealrate[i][2]);
        fclose(setfile);

        printf("Success!!Press any key..");
        getch();

        break;

    case 7:
        system("cls");
        printf("\nEnter Old Password    : ");
            for(i=0;(c=getch()) != '\r';i++)
            {
                if(c == '\b' && i != 0)
                {
                    printf("\b \b");
                    i = i-2;
                }
                else if(c != '\b')
                {
                    oldpass[i] = c;
                    printf("*");
                }
                else
                    i--;
            }

            oldpass[i] = '\0';

        if(strcmp(oldpass,set.pass) == 0)
        {
            printf("\nEnter New Password    : ");
                for(i=0;(c=getch()) != '\r';i++)
                {
                    if(i==40 && c != '\b')
                        i--;

                    else if(c == '\b' && i != 0)
                    {
                        printf("\b \b");
                        i = i-2;
                    }
                    else if(c != '\b')
                    {
                        newpass[i] = c;
                        printf("*");
                    }
                    else
                        i--;
                }

                newpass[i] = '\0';

            printf("\nRe-Enter New Password : ");
                for(i=0;(c=getch()) != '\r';i++)
                {
                    if(i==40 && c != '\b')
                        i--;

                    else if(c == '\b' && i != 0)
                    {
                        printf("\b \b");
                        i = i-2;
                    }
                    else if(c != '\b')
                    {
                        renewpass[i] = c;
                        printf("*");
                    }
                    else
                        i--;
                }

                renewpass[i] = '\0';

            if(strcmp(newpass,renewpass) == 0)
            {
                strcpy(set.pass,renewpass);

                for(i=0;renewpass[i];i++)
                    renewpass[i] -= 15;

                    cfgfile = fopen("hms_config.dat", "w");
                        fprintf(cfgfile,"%s", renewpass);
                    fclose(cfgfile);

                printf("\nPassword has been changed!!\n");
            }

            else
                printf("\nPassword does not match.. Please try again\n\n");
        }
        else
            printf("\nEntered password is wrong!!\n");

        getch();
        break;

    case 0:
        menu();
        break;

    default:
        system("cls");
        printf("Wrong Choice.\nPress any key to go back.. ");
        getch();
        settings();
        break;
    }

    settings();
}


void generate_html(void)
{
        FILE *data, *html;
        char bill[100] = "bills\\hms_bill_";
        int i,j,CountMeals=0,CountDay=0;
        double meal_charge = 0, bill_srvcharge, bill_total, bill_meal;

        for(j=0;j<set.days;j++)
            meal_charge += set.mealrate[j][0] + set.mealrate[j][1] + set.mealrate[j][2];

        mkdir("bills");
        strcat(bill,set.year);
        strcat(bill,"-");
        strcat(bill,set.mm);
        strcat(bill,".html");

        printf("Press any key to generate bill. ");
        getch();

        data = fopen("hms_data.dat","r");
        html = fopen(bill,"w");
            fprintf(html,"<html>\n<head>\n<title>Bill Info || Student Hall Management System</title>\n</head>\n\n<style>\ntd,th {padding: 2px 5px 2px 5px;}\nthead {display: table-header-group;}\ntfoot {display: table-header-group;}\n</style>\n\n<body>\n");
            fprintf(html,"<table border=\"1\" style=\"border: none; border-collapse: collapse\">\n<thead><b><tr><th colspan=\"3\" style=\"border:none\">Month: %s-%s</th> <th colspan=\"9\" style=\"border:none\">%s, Hall Bill Summary</th></tr><b><tr> <th align = \"center\"><b>Room</b></th> <th align = \"center\"><b>Roll</b></th> <th align = \"center\"><b>Name</b></th> <th align = \"center\"><b>Dept.</b></th> <th align = \"center\"><b>Batch</b></th> <th align = \"center\"><b>Number of Meal</b></th> <th align = \"center\"><b>Meal Charge (%.2lf)</b></th> <th align = \"center\"><b>Service Charge (%.lf%%)</b></th> <th align = \"center\"><b>Fuel & Spices</b></th> <th align = \"center\"><b>Hall Charge</b></th> <th align = \"center\"><b>Total</b></th> <th align = \"center\"><b>Signature</b></th> <th align = \"center\"><b>Remarks</b></th> </tr></thead>\n", set.month, set.year, set.hallname_s, meal_charge, set.srvcharge);

            while(fscanf(data,"%s %s %s %s %s %s %s %s", &std.room, &std.roll, &std.name, &std.dept, &std.batch, &std.phone, &std.district, &temp) != EOF)
            {
                CountMeals = 0;
                CountDay = 0;

                for(j=0;j<31;j++)
                    {
                       fscanf(data,"%s", &chk.mealday[j]);
                    }

                for(j=0;j<set.days;j++)
                {
                    if(chk.mealday[j][2] == '1')
                        CountMeals++;

                    if(chk.mealday[j][3] == '1')
                        CountMeals++;

                    if(chk.mealday[j][4] == '1')
                        CountMeals++;

                    if(chk.mealday[j][2] == '1' || chk.mealday[j][3] == '1' || chk.mealday[j][4] == '1')
                        CountDay++;
                }

                for(i=0;i<strlen(std.name);i++)
                {
                    if(std.name[i] == '#')
                        std.name[i] = ' ';
                }

                if(CountDay == 0)
                    set.fuel_std = 0;
                else
                    set.fuel_std = set.fuel;

                bill_meal = 0;
                for(j=0;j<set.days;j++)
                {
                    bill_meal += (chk.mealday[j][2]=='1'?set.mealrate[j][0]:0) + (chk.mealday[j][3]=='1'?set.mealrate[j][1]:0) + (chk.mealday[j][4]=='1'?set.mealrate[j][2]:0);
                }

                bill_srvcharge = bill_meal * (set.srvcharge/100);
                bill_total = bill_meal + bill_srvcharge + set.fuel_std + set.hallcharge;

                fprintf(html,"<tr> <td align = \"center\">%s</td> <td align = \"center\">%s</td> <td width=\"250\" align = \"left\">%s</td> <td align = \"center\">%s</td> <td align = \"center\">%s</td> <td align = \"center\">%d</td> <td align = \"center\">%.2lf</td> <td align = \"center\">%.2lf</td> <td align = \"center\">%.2lf</td> <td align = \"center\">%d</td> <th align = \"center\"><b>%.2lf</b></th> <td align = \"center\"> </td> <td align = \"center\"> </td> </tr>\n", std.room, std.roll, std.name, std.dept, std.batch, CountMeals, bill_meal, bill_srvcharge, set.fuel_std, set.hallcharge, bill_total);
            }


            fprintf(html,"</table>\n");
            fprintf(html,"</body>\n\n</html>");
        fclose(data);
        fclose(html);

        printf("\nDone. HTML File Generated in %s. Press any key to go back\n", bill);
        getch();
}
