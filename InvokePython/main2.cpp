 //һ��Ϊ����ʵ������һ�׷���  
 #include < Python.h> 
 #include < conio.h> 
 int main() 
  {  Py_Initialize(); 
  	 if (!Py_IsInitialized()) 
  	 	 {  printf("��ʼ������\n");
  	 	 	  return -1;  
  	 	 	  }  
  	 	 	  PyObject* pModule = NULL;  PyObject* pFunc = NULL;  PyObject* pArg = NULL; 
  	 	 	   PyObject* pRetVal = NULL;  
  	 	 	   pModule = PyImport_ImportModule("hello"); 
  	 	 	    pFunc = PyObject_GetAttrString(pModule,"hello"); 
  	 	 	     pArg = Py_BuildValue("(i,i)",33,44);  
  	 	 	     pRetVal = PyObject_CallObject(pFunc,pArg); 
  	 	 	      printf("%d\n",PyInt_AsLong(pRetVal));
  	 	 	        Py_Finalize(); 
  	 	 	         _getch(); 
  	 	 	         return 0;  } 
			
		
		
		
	
	
	