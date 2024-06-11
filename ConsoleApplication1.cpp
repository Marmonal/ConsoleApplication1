class CGoldenRatioTradingBot {
private:
    double* historical_prices;
    int historical_prices_size;
    double golden_ratio;

public:
    static const double DEFAULT_GOLDEN_RATIO = 1.618;
    static const std::string BACKTESTING_RESULT_MESSAGE = "Resultados del backtesting:";

    CGoldenRatioTradingBot(const double _historical_prices[], int size, double _golden_ratio = DEFAULT_GOLDEN_RATIO)
        : golden_ratio(_golden_ratio), historical_prices_size(size) {
        historical_prices = new double[size];
        for (int i = 0; i < size; i++) {
            historical_prices[i] = _historical_prices[i];
        }
    }

    ~CGoldenRatioTradingBot() {
        delete[] historical_prices;
    }

    double CalculateGoldenPrice(double previous_price) {
        return previous_price * golden_ratio;
    }

    void backtest_strategy() {
        if (historical_prices_size == 0) {
            throw std::runtime_error("No hay precios históricos para realizar el backtesting");
        }

        bool* buy_signals = new bool[historical_prices_size];

        for (int i = 1; i < historical_prices_size; i++) {
            double previous_price = historical_prices[i - 1];
            double current_price = historical_prices[i];
            double golden_price = CalculateGoldenPrice(previous_price);

            bool buy_signal = (current_price > golden_price);
            buy_signals[i] = buy_signal;
        }

        evaluate_strategy(buy_signals, historical_prices_size);

        delete[] buy_signals;
    }

    void evaluate_strategy(const bool* signals, int size) {
        std::cout << BACKTESTING_RESULT_MESSAGE << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << (signals[i] ? "Comprar" : "No comprar") << std::endl;
        }
    }
};

void OnStart() {
    double historical_prices[] = { 100, 110, 120, 130, 140, 150, 160, 170, 180, 190 };
    int size = sizeof(historical_prices) / sizeof(historical_prices[0]);

    CGoldenRatioTradingBot bot(historical_prices, size);
    bot.backtest_strategy();
}