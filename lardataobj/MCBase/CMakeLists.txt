cet_make( LIBRARIES nusimdata_SimulationBase
		              ROOT::Core
                    ROOT::Physics
                    NO_DICTIONARY )

art_dictionary( DICTIONARY_LIBRARIES lardataobj_MCBase )

install_headers()
install_fhicl()
install_source()
