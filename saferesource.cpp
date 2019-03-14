#include <eosio.token/eosio.token.hpp>

using namespace eosio;

#define ramAsset asset(20000, S(4, GOC))
#define netAsset asset(10000, S(4, GOC))
#define cpuAsset asset(70000, S(4, GOC))

class saferesource : contract
{
public:
  using contract::contract;
  saferesource(name self) : contract(self) {}

  // @abi action
  void sendres(account_name from, account_name to)
  {
    require_auth(from);

    //buyram
    action(permission_level{from, N(active)}, N(gocio), N(buyram),
           std::make_tuple(from, to, ramAsset))
        .send();

    //delegatebw
    action(permission_level{from, N(active)}, N(gocio), N(delegatebw),
           std::make_tuple(from, to, netAsset, cpuAsset, false))
        .send();
  }
};
EOSIO_ABI(saferesource, (sendres))