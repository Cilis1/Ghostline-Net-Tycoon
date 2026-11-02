#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Ghostline's game simulation in standard C++17; no third-party engine required.
struct Service { std::string name, blurb; int cost, credits, users, trace, unlock; };
struct Site { int service = -1, level = 0; };
class Game {
    const std::array<Service, 6> services{{
        {"Community Forum", "A quiet place for the old Net to talk.", 45, 2, 3, 0, 0},
        {"Virtual Arcade", "A little joy goes a long way.", 75, 7, 1, 0, 0},
        {"Mirror Archive", "Keep forgotten knowledge alive.", 110, 1, 4, 0, 50},
        {"Relay Hub", "Boost nearby services by ten percent.", 130, 0, 0, 0, 50},
        {"Privacy Vault", "Scrub two Trace per minute.", 160, 0, 0, -2, 100},
        {"Stream Den", "Big returns, but hard to hide.", 190, 12, 2, 2, 100}
    }};
    std::array<Site, 6> sites{};
    double credits = 130, users = 0, trace = 0;
    int minute = 0;
public:
    void status() const {
        double income = 0, growth = 0, risk = 0;
        for (const auto& site : sites) if (site.service >= 0) {
            const auto& s = services[site.service]; const double mult = 1 + .5 * (site.level - 1);
            income += s.credits * mult; growth += s.users * mult; risk += s.trace;
        }
        if (sites[3].service >= 0) { income *= 1.1; growth *= 1.1; }
        std::cout << "\n\033[95m╔════════════════ G H O S T L I N E ════════════════╗\033[0m\n"
                  << "  ¢ " << static_cast<int>(credits) << "   USERS " << static_cast<int>(users)
                  << "   TRACE " << static_cast<int>(trace) << "/100   [";
        int filled = std::clamp(static_cast<int>(trace / 10), 0, 10);
        for (int i=0;i<10;++i) std::cout << (i<filled ? "■" : "·");
        std::cout << "]\n  MESH / ABANDONED MESH     NET YIELD +" << income << "¢ / MIN · +" << growth << " USERS / MIN\n"
                  << "\033[95m╚═══════════════════════════════════════════════════╝\033[0m\n";
        for (int i=0;i<6;++i) {
            std::cout << "  " << i+1 << ". ";
            if (sites[i].service >= 0) std::cout << "\033[96m" << services[i].name << " · LEVEL " << sites[i].level << " ONLINE\033[0m";
            else if (users < services[i].unlock) std::cout << "[LOCKED] " << services[i].name << " — requires " << services[i].unlock << " users";
            else std::cout << "[OPEN]   " << services[i].name << " — " << services[i].cost << " credits";
            std::cout << '\n';
        }
        if (trace >= 60) std::cout << "\033[91m  !! CORPORATE SCAN DETECTED — reduce Trace with a Privacy Vault.\033[0m\n";
        if (trace >= 80) std::cout << "  Sweep imminent. At 100 Trace, a risky service goes offline briefly.\n";
        std::cout << "  CONTRACT: Build a service · reward +60 credits\n";
    }
    void run() {
        std::cout << "\033[96mGhostline: Net Tycoon — C++17 edition\033[0m\nA forgotten corner of cyberspace is yours. Build a network they can't own.\n";
        bool contracted = false;
        for (;;) {
            status(); std::cout << "\n[A] Build/upgrade  [T] Wait one minute  [Q] Quit\n> ";
            std::string cmd; if (!(std::cin >> cmd)) break;
            if (cmd == "q" || cmd == "Q") break;
            if (cmd == "t" || cmd == "T") {
                double income=0,growth=0,risk=0;
                for (auto site:sites) if(site.service>=0){auto s=services[site.service];double m=1+.5*(site.level-1);income+=s.credits*m;growth+=s.users*m;risk+=s.trace;}
                if(sites[3].service>=0){income*=1.1;growth*=1.1;} credits+=income;users+=growth;trace=std::max(0.0,trace+risk);++minute;
                if(trace>=100){for(auto& site:sites)if(site.service==5){site.service=-1;site.level=0;break;}trace=55;std::cout<<"\033[91mCorporate sweep! A risky service was temporarily interrupted; the network survives.\033[0m\n";}
                if(users>=100)std::cout<<"\033[96mNeon Commons route unlocked!\033[0m\n";
            } else if(cmd=="a"||cmd=="A") {
                std::cout << "Site number (1-6): ";int n;std::cin>>n;if(n<1||n>6)continue;auto& site=sites[n-1];
                if(site.service>=0){auto& s=services[site.service];int price=static_cast<int>(s.cost*(1+.72*site.level));if(site.level>=3)std::cout<<"Already at maximum level.\n";else if(credits<price)std::cout<<"Not enough credits.\n";else{credits-=price;++site.level;std::cout<<s.name<<" upgraded.\n";}}
                else {auto& s=services[n-1];if(users<s.unlock)std::cout<<"Route locked. Grow your audience first.\n";else if(credits<s.cost)std::cout<<"Not enough credits.\n";else{credits-=s.cost;site={n-1,1};std::cout<<s.name<<" is online.\n";if(!contracted){credits+=60;contracted=true;std::cout<<"Contract complete: +60 credits.\n";}}}
            }
        }
        std::cout << "\nSession ended. Your network is still out there.\n";
    }
};
int main(){Game game;game.run();}
