#ifndef HOSPITAL_SYSTEM_INTERFACE
#define HOSPITAL_SYSTEM_INTERFACE


#define HOSPITALSYSTEM_MAX_PATIENTS 5
#define HOSPITALSYSTEM_MAX_SPEC     20
#define HOSPITALSYSTEM_MAX_STATUS   3


#define HOSPITALSYSTEM_ADD_PATIENT               1
#define HOSPITALSYSTEM_GET_NEXT_PATIENT          2
#define HOSPITALSYSTEM_PRINT_PATIENTS            3
#define HOSPITALSYSTEM_PRINT_PATIENTS_FOR_SPEC   4
#define HOSPITALSYSTEM_EXIT                      5

#define HOSPITALSYSTEM_REGULAR_STATUS   0
#define HOSPITALSYSTEM_URGENT_STATUS    1
#define HOSPITALSYSTEM_NO_STATUS        2


typedef enum 
{
    hospitalSystem_ValidOperation,
    hospitalSystem_InvalidStatus,
    hospitalSystem_MaxQueueLength,
    hospitalSystem_NoPatients
}HospitalSystem_ReturnValues_t;

const string HosSys_PatientsStatus[HOSPITALSYSTEM_MAX_STATUS] = { "Urgent", "Regular", "No Status" };


struct Patient_Info
{
    string patientName;
    int patientStatus;

    Patient_Info()
    {
        patientName = "No Name";
        patientStatus = HOSPITALSYSTEM_NO_STATUS;
    }

    Patient_Info( string copy_PatientName, int copy_PatientStatus )
    {
        patientName = {copy_PatientName};
        patientStatus = {copy_PatientStatus};
    }

};


struct HospitalSystem_Queues 
{
    Patient_Info HosSys_Patients[HOSPITALSYSTEM_MAX_PATIENTS];
    int HosSys_Queuelength;
    int HosSys_QueueSpecitialization;

    HospitalSystem_Queues()
    {
        HosSys_Queuelength = 0;
        HosSys_QueueSpecitialization = -1;
    }

    HospitalSystem_Queues( int copy_QueueSpecitialization )
    {
        HosSys_Queuelength = 0;
        HosSys_QueueSpecitialization = {copy_QueueSpecitialization};
    }

    // add patient function
    HospitalSystem_ReturnValues_t HosSys_AddPatient( string copy_PatientName, int copy_PatientStatus )
    {
        // no patients can be added to the queue if the queue length reached the max number of patients
        if ( HosSys_Queuelength >= HOSPITALSYSTEM_MAX_PATIENTS ) return hospitalSystem_MaxQueueLength;

        Patient_Info HosSys_NewPatient{ copy_PatientName, copy_PatientStatus };


        // check for the status of the patient
        if (copy_PatientStatus == HOSPITALSYSTEM_URGENT_STATUS)
        {
            int i = 0;

            // get the first patient with status not urgent
            while (HosSys_Patients[i].patientStatus == HOSPITALSYSTEM_URGENT_STATUS) { i++; }

            // now iterator is at the first patient with regular status 
            // we need to add the new patient at this place as he is urgent and the other patient is regular
            for (size_t j = HosSys_Queuelength; j > i ; j--) { HosSys_Patients[j] = HosSys_Patients[j - 1]; }
            
            // add the new patient after all urgent patients
            HosSys_Patients[i] = {HosSys_NewPatient};

            // increment the queue length
            HosSys_Queuelength++;
        }
        // add the patient at the end of the queue of his status is regular
        else if (copy_PatientStatus == HOSPITALSYSTEM_REGULAR_STATUS) { HosSys_Patients[HosSys_Queuelength++] = {HosSys_NewPatient}; }

        return hospitalSystem_ValidOperation;
    }


    // get patient function
    HospitalSystem_ReturnValues_t HosSys_GetPatient()
    {
        // check if the queue is empty or not
        // if empty so no patients to get
        if ( HosSys_Queuelength == 0 ) return hospitalSystem_NoPatients;

        // if the queue is not empty just move the first patient and shift all patients to left
        cout << endl << "Patient " << HosSys_Patients[0].patientName << " is entering to the doctor now..." << endl << endl;
        for (size_t i = 1; i < HosSys_Queuelength; i++) { HosSys_Patients[i - 1] = HosSys_Patients[i]; }

        // decrement the queue length as now the first patient is out of the queue
        HosSys_Queuelength--;

        return hospitalSystem_ValidOperation;
    }


    // print patients function
    HospitalSystem_ReturnValues_t HosSys_PrintSpecPatient()
    {
        cout << "-------------------------------------" << endl;
        cout << "Specialization " << HosSys_QueueSpecitialization << endl << endl;
        if (HosSys_Queuelength == 0) 
        { 
            cout << "No Patients yet" << endl << endl; 
            cout << "-------------------------------------" << endl;
            return hospitalSystem_NoPatients;
        }

        for (size_t i = 0; i < HosSys_Queuelength; i++)
        {   
            cout << "Name: " << HosSys_Patients[i].patientName << endl;
            cout << "Status: " << HosSys_PatientsStatus[HosSys_Patients[i].patientStatus] << endl << endl;
        }
        cout << "-------------------------------------" << endl;
        
        return hospitalSystem_ValidOperation;
    }
};


struct Hospital_System_Program
{
    HospitalSystem_Queues System_Queues[HOSPITALSYSTEM_MAX_SPEC];

    Hospital_System_Program()
    {
        for (size_t i = 0; i < HOSPITALSYSTEM_MAX_SPEC; i++)
        {
            System_Queues[i] = HospitalSystem_Queues(i+1);
        }
    }

    void System_Run()
    {
        int System_Choice;
        do
        {
            System_Choice = HosSys_ConsoleScreen();

            if ( System_Choice == HOSPITALSYSTEM_ADD_PATIENT )
            {
                System_AddPatient();
            }
            else if ( System_Choice == HOSPITALSYSTEM_GET_NEXT_PATIENT )
            {
                System_GetPatient();
            }
            else if ( System_Choice == HOSPITALSYSTEM_PRINT_PATIENTS )
            {
                System_PrintPatients();
            }
            else if ( System_Choice == HOSPITALSYSTEM_PRINT_PATIENTS_FOR_SPEC )
            {
                System_PrintPatientsForSpec();
            }
            else if ( System_Choice == HOSPITALSYSTEM_EXIT )
            {
                cout << "Thanks for using Hospital System..." << endl;
            }
            else
            {
                cout << "Invalid Input!! please choose number from 1 to 5..." << endl;
            }
            
        } while (System_Choice != HOSPITALSYSTEM_EXIT);
        
    }


    // add patient function
    void System_AddPatient()
    {
        HospitalSystem_ReturnValues_t AddPatient_ReturnValue;
        int System_SpecChoice, System_PatientStatus;
        string System_PatientName;

        do
        {
            System_SpecChoice = HosSys_SpecScreen();
            if (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC) { cout << "You entered a wrong specialization..." << endl; }
        } while (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC || System_SpecChoice < 1);

        if (System_Queues[System_SpecChoice - 1].HosSys_Queuelength > HOSPITALSYSTEM_MAX_PATIENTS) { cout << "Sorry!! Can't add more Patients the queue reached it's maximum length." << endl << endl; }
        else 
        { 
            cout << "Enter Patient Name: " << endl;
            getline(cin >> ws, System_PatientName);

            do
            {
                System_PatientStatus = HosSys_StatusScreen();
                if (System_PatientStatus > HOSPITALSYSTEM_MAX_STATUS) { cout << "You entered a wrong status..." << endl; }
            } while (System_PatientStatus != HOSPITALSYSTEM_URGENT_STATUS && System_PatientStatus != HOSPITALSYSTEM_REGULAR_STATUS);


            AddPatient_ReturnValue = System_Queues[System_SpecChoice - 1].HosSys_AddPatient(System_PatientName, System_PatientStatus);

            if (AddPatient_ReturnValue == hospitalSystem_MaxQueueLength) { cout << "Sorry!! Can't add more Patients the queue reached it's maximum length." << endl << endl; }
            else { cout << "Patient " << System_PatientName << " is added successfully to the queue of specialization " << System_SpecChoice << endl; }
        }
    }

    // get patient function
    void System_GetPatient()
    {
        HospitalSystem_ReturnValues_t GetPatient_ReturnValue;
        int System_SpecChoice;

        do
        {
            System_SpecChoice = HosSys_SpecScreen();
            if (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC) { cout << "You entered a wrong specialization..." << endl; }
        } while (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC || System_SpecChoice < 1);

        GetPatient_ReturnValue = System_Queues[System_SpecChoice - 1].HosSys_GetPatient();

        if (GetPatient_ReturnValue == hospitalSystem_NoPatients) { cout << "Sorry!! No patients in the queue yet.." << endl; }
    }


    // print patients function
    void System_PrintPatients()
    {
        for (size_t i = 0; i < HOSPITALSYSTEM_MAX_SPEC; i++)
        {
            System_Queues[i].HosSys_PrintSpecPatient();
        } 
    }


    void System_PrintPatientsForSpec()
    {
        int System_SpecChoice;

        do
        {
            System_SpecChoice = HosSys_SpecScreen();
            if (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC) { cout << "You entered a wrong specialization..." << endl; }
        } while (System_SpecChoice > HOSPITALSYSTEM_MAX_SPEC || System_SpecChoice < 1);

        System_Queues[System_SpecChoice - 1].HosSys_PrintSpecPatient();
    }



    // printing functions

    int HosSys_ConsoleScreen(void)
    {
        int HosSys_Choice;

        cout << "Enter your choice:" << endl;
        cout << "1) Add new patient" << endl;
        cout << "2) Get new patient" << endl;
        cout << "3) Print all patients" << endl;
        cout << "4) Print patients for single specialization" << endl;
        cout << "5) Exit" << endl;

        // get the choice from the user
        cin >> HosSys_Choice;

        return HosSys_Choice;
    }


    int HosSys_SpecScreen(void)
    {
        int HosSys_SpecChoice;
        cout << "------------------------------------------------------" << endl;
        for (size_t i = 1; i <= HOSPITALSYSTEM_MAX_SPEC; i++)
        {
            cout << i << "- Specialization " << i << endl;
        }
        cout << "------------------------------------------------------" << endl;

        cout << "Please enter a number from 1 to " << HOSPITALSYSTEM_MAX_SPEC << " to choose one of the above specialization: " << endl;
        cin >> HosSys_SpecChoice;

        return HosSys_SpecChoice;
    }


    int HosSys_StatusScreen(void)
    {
        int HosSys_StatusChoice;
        
        cout << "Please enter 0 for Urgent status or 1 for Regular status: " << endl;
        cin >> HosSys_StatusChoice;

        return HosSys_StatusChoice;
    }

};



#endif /* HOSPITAL_SYSTEM_INTERFACE */