/*
 * 
 * 
 *   Drip Irigation System
 *                                        hose1    
 *       WaterIn                 [S1]--------------}        
 *           \ ________         /         hose2  
 *            /        \       //[S2]--------------}  
 *           ( H2O Tank ) ->->((          hose3  
 *            \________/       \\[S3]--------------}
 *                              \         hose4
 *                               [S4]--------------}
 *   
 *                              
 *   
 *   Electrical System                                       _ /
 *                                              ________     \\ /
 *                              3A             / (+ -)  \     \\ /
 *                   ---------(Fuse)----------( 12v Btry )-----\\ / Solar
 *      Analog     /                           \________/       \\ /
 *    [BtryTest]--O                              |    |          \\ /         
 *         |      |                              |    |           \\ /                       
 *          \  ___|___                      /--[S1]---|            \\
 *           \/ (vin) \  Solenoid Signals  //--[S2]---|
 *           | Arduino |==================//---[S3]---|                                              
 *         __|   Nano  |                   \_ _[S4]---|
 *       /    \_______/\                              |
 *      |        ||     \_ _ _ _ _ _ _ _ _ _ [Btn1]---|                                    
 *    [Gnd]      ||         Digital Btns    \[Btn2]---|                         
 *             Analog                                 |
 *               ||_ _ _ _ _ _ _                      |     
 *               /|\  \  \  \    \                    |        
 *              / | \  \  \  \   [Photo]              |
 *          [T1][T2] \  \  \  \  Resistor           [Gnd]
 *                   |  |   |  \                    
 *                 [H1][H2][H3][H4]                 
 *                 
 */


    
                        

