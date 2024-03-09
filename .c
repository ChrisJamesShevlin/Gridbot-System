#property strict

// Input parameters
input double TakeProfitPips = 10.0;
input double DistancePips = 5.0;
double firstBuyPrice = 0.0;
double firstSellPrice = 0.0;

// New variables for profit tracking
double totalProfitPoints = 0.0;
bool tradingEnabled = true; // Control flag for enabling or disabling trading

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
   // Place initial Buy and Sell orders
   firstBuyPrice = NormalizeDouble(Ask, _Digits);
   firstSellPrice = NormalizeDouble(Bid, _Digits);
   
   int ticketBuy = OrderSend(Symbol(), OP_BUY, 0.01, Ask, 2, 0, firstBuyPrice + TakeProfitPips * Point, "First Buy", 0, 0, clrGreen);
   int ticketSell = OrderSend(Symbol(), OP_SELL, 0.01, Bid, 2, 0, firstSellPrice - TakeProfitPips * Point, "First Sell", 0, 0, clrRed);
   
   if(ticketBuy < 0 || ticketSell < 0)
     {
      Print("Error opening initial orders: ", GetLastError());
     }
   
   return(INIT_SUCCEEDED);
  }

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
   // Check if trading is enabled
   if(!tradingEnabled) return;
   
   // Trading logic here...
   
   // Example: Update totalProfitPoints based on your profit calculation
   // This is a simplified placeholder. You'll need to replace it with your actual profit calculation logic.
   // if(profitConditionMet) {
   //     totalProfitPoints += calculatedPointsProfit;
   // }
   
   // Check if the profit goal has been reached and disable further trading
   if(totalProfitPoints >= 10) {
      tradingEnabled = false;
      Print("Profit target reached. Trading disabled.");
   }
  }
