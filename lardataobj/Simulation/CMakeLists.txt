cet_make( LIBRARIES nusimdata_SimulationBase
                    canvas
                    MF_MessageLogger
                   cetlib
                   cetlib_except
                   ROOT::Core
                   ROOT::Physics
                   NO_DICTIONARY)

art_dictionary( DICTIONARY_LIBRARIES lardataobj_Simulation )

install_headers()
install_source()
