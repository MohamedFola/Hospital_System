#include<iostream>

using namespace std;


#include "Hospital_System_Interface.hpp"


int main()
{
    // HospitalSystem_Queues H(2);

    // H.HosSys_AddPatient("Mohamed", HOSPITALSYSTEM_URGENT_STATUS); // mohamed
    // H.HosSys_AddPatient("Hassan", HOSPITALSYSTEM_REGULAR_STATUS); // mohamed hassan
    // H.HosSys_AddPatient("Foula", HOSPITALSYSTEM_REGULAR_STATUS); // mohamed hassan foula
    // H.HosSys_AddPatient("Ahmed", HOSPITALSYSTEM_URGENT_STATUS); // mohamed ahmed hassan foula
    // H.HosSys_AddPatient("Hamed", HOSPITALSYSTEM_URGENT_STATUS); // mohamed ahmed hamed hassan foula
    // H.HosSys_AddPatient("Adbo", HOSPITALSYSTEM_URGENT_STATUS); // max queue

    // H.HosSys_PrintSpecPatient();

    // H.HosSys_GetPatient(); // ahmed hamed hassan foula
    // H.HosSys_GetPatient(); // hamed hassan foula

    // H.HosSys_PrintSpecPatient();
    Hospital_System_Program H;

    H.System_Run();


    return 0;
}
