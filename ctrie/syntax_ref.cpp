//FUNCTION POINTERS
// auto function = func_pointer; 

// typedef void(*TYPE_NAME)(FUNC_PARAM_TYPES);
// TYPE_NAME FUNCTION_NAME = FUNCTION_POINTER;

//PASSING FUNCTIONS TO OTHER FUNCTIONS 
// type FUNC2(param_types)
// {
//     do things
// }
// void FUNC1(type(*FUNC2_NAME)(param_types))
// {
//     FUNC2_NAME(params);
// }

//lamda functions in function calls
// FUNC1(params, params, [](lambda_func_params){function_body});