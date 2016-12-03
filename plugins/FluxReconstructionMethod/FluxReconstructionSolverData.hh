// Copyright (C) 2012 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef COOLFluiD_Numerics_FluxReconstructionMethod_FluxReconstructionSolverData_hh
#define COOLFluiD_Numerics_FluxReconstructionMethod_FluxReconstructionSolverData_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/GeometricEntityPool.hh"
#include "Framework/LinearSystemSolver.hh"
#include "Framework/ConvergenceMethod.hh"
#include "Framework/MultiMethodHandle.hh"
#include "Framework/SpaceMethodData.hh"
#include "Framework/StdTrsGeoBuilder.hh"
//#include "Framework/VolumeIntegrator.hh"
#include "Framework/FaceToCellGEBuilder.hh"

#include "Framework/DofDataHandleIterator.hh"
#include "Framework/ProxyDofIterator.hh"

#include "Framework/DataSocketSource.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {
  namespace FluxReconstructionMethod {

    class BCStateComputer;
    class FluxReconstructionStrategy;
    class BaseInterfaceFlux;
    class BasePointDistribution;
    class FluxReconstructionElementData;
    class ReconstructStatesFluxReconstruction;
    class BasePointDistribution;
    class BaseBndFaceTermComputer;

//////////////////////////////////////////////////////////////////////////////

/// This class represents data object accessed by different FluxReconstructionSolverCom's
/// @author Alexander Papen
/// @author Ray Vandenhoeck
class FluxReconstructionSolverData : public Framework::SpaceMethodData {

public: // functions

  /// Defines the Config Option's of this class
  /// @param options a OptionList where to add the Option's
  static void defineConfigOptions(Config::OptionList& options);

  /// Constructor
  FluxReconstructionSolverData(Common::SafePtr<Framework::Method> owner);

  /// Destructor
  ~FluxReconstructionSolverData();

  /// Configure the data from the supplied arguments
  virtual void configure ( Config::ConfigArgs& args );

  /// Sets the LinearSystemSolver for this SpaceMethod to use
  /// @pre LinearSystemSolver pointer is not constant to allow dynamic_casting
  void setLinearSystemSolver(
    Framework::MultiMethodHandle< Framework::LinearSystemSolver > lss )
  {
    m_lss = lss;
  }

  /// Get the linear system solver
  Framework::MultiMethodHandle< Framework::LinearSystemSolver >
    getLinearSystemSolver() const
  {
    cf_assert(m_lss.isNotNull());
    return m_lss;
  }

  /// Sets the ConvergenceMethod for this SpaceMethod to use
  /// @pre the pointer to ConvergenceMethod is not constant to
  ///      allow dynamic_casting
  void setConvergenceMethod(Framework::MultiMethodHandle<Framework::ConvergenceMethod> convMtd)
  {
    m_convergenceMtd = convMtd;
  }

  /// Get the ConvergenceMethod
  Framework::MultiMethodHandle<Framework::ConvergenceMethod> getConvergenceMethod() const
  {
    cf_assert(m_convergenceMtd.isNotNull());
    return m_convergenceMtd;
  }


  /// @return the GeometricEntity builder
  Common::SafePtr<
    Framework::GeometricEntityPool< Framework::StdTrsGeoBuilder > >
    getStdTrsGeoBuilder()
  {
    return &m_stdTrsGeoBuilder;
  }


  /// Gets the Class name
  static std::string getClassName()
  {
    return "FluxReconstructionSolver";
  }
  
  /// @return the boundary face term computer
  Common::SafePtr< BaseBndFaceTermComputer > getBndFaceTermComputer()
  {
    return m_bndFaceTermComputer.getPtr();
  }

//   /// Get the VolumeIntegrator
//   Common::SafePtr< Framework::VolumeIntegrator > getVolumeIntegrator();
  
  /// Gets the interface flux computation strategy
  Common::SafePtr< BaseInterfaceFlux > getInterfaceFlux() const
  {
    cf_assert(m_interfaceflux.isNotNull());
    return m_interfaceflux.getPtr();
  }
  
  /// Gets the flux point distribution
  Common::SafePtr< BasePointDistribution > getFluxPntDistribution() const
  {
    cf_assert(m_fluxpntdistribution.isNotNull());
    return m_fluxpntdistribution.getPtr();
  }
  
  /// Gets the solution point distribution
  Common::SafePtr< BasePointDistribution > getSolPntDistribution() const
  {
    cf_assert(m_solpntdistribution.isNotNull());
    return m_solpntdistribution.getPtr();
  }
  
  /// @return reference to m_frLocalData
  std::vector< FluxReconstructionElementData* >& getFRLocalData();
  
  /// @return the states reconstructor
  Common::SafePtr< ReconstructStatesFluxReconstruction > getStatesReconstructor();
  
    /// @return the GeometricEntity face builder
  Common::SafePtr<
    Framework::GeometricEntityPool< Framework::FaceToCellGEBuilder > >
    getFaceBuilder()
  {
    return &m_faceBuilder;
  }
  
  /// @return the BCStateComputers
  Common::SafePtr< std::vector< Common::SafePtr< BCStateComputer > > > getBCStateComputers()
  {
    return &m_bcsSP;
  }
  
  /// @return m_bcNameStr
  std::vector< std::string >& getBCNameStr()
  {
    return m_bcNameStr;
  }

  /// @return m_bcTRSNameStr
  Common::SafePtr< std::vector< std::vector< std::string > > > getBCTRSNameStr()
  {
    return &m_bcTRSNameStr;
  }
  
  /// set m_resFactor
  void setResFactor(CFreal resFactor)
  {
    m_resFactor = resFactor;
  }
  
  /// @return m_resFactor
  CFreal getResFactor()
  {
    return m_resFactor;
  }
  
  /// set m_maxNbrRFluxPnts
  void setMaxNbrRFluxPnts(CFuint maxNbrRFluxPnts)
  {
    m_maxNbrRFluxPnts = maxNbrRFluxPnts;
  }
  
  /// @return m_maxNbrRFluxPnts
  CFuint getMaxNbrRFluxPnts()
  {
    return m_maxNbrRFluxPnts;
  }
  
  /// @return reference to m_bndFacesStartIdxs
  std::map< std::string , std::vector< std::vector< CFuint > > >& getBndFacesStartIdxs()
  {
    return m_bndFacesStartIdxs;
  }
  
  /// @return m_maxNbrStatesData
  CFuint getMaxNbrStatesData()
  {
    return m_maxNbrStatesData;
  }
  
  /// set m_maxNbrStatesData
  void setMaxNbrStatesData(CFuint maxNbrStatesData)
  {
    m_maxNbrStatesData = maxNbrStatesData;
  }
  
  /// @return reference to m_innerFacesStartIdxs
  std::vector< CFuint >& getInnerFacesStartIdxs()
  {
    return m_innerFacesStartIdxs;
  }

  
  /// Sets up the FluxReconstructionData
  void setup();
  
  /// Unsets the method data
  void unsetup();
  
//   /// Returns the DataSocket's that this command provides as sources
//   /// @return a vector of SafePtr with the DataSockets
//   std::vector< Common::SafePtr< Framework::BaseDataSocketSource > >
//     providesSockets();

private:  // helper functions

//   /// Configures the ContourIntegrator and the IntegrableEntity
//   void configureIntegrator();
  
  /**
   * Creates the local data for FR
   */
  void createFRLocalData();

private:  // data

  /// Linear system solver
  Framework::MultiMethodHandle< Framework::LinearSystemSolver > m_lss;

  /// Convergence Method
  Framework::MultiMethodHandle<Framework::ConvergenceMethod> m_convergenceMtd;

  /// Builder for standard TRS GeometricEntity's
  Framework::GeometricEntityPool< Framework::StdTrsGeoBuilder > m_stdTrsGeoBuilder;
  
  /// Builder for faces (containing the neighbouring cells)
  Framework::GeometricEntityPool< Framework::FaceToCellGEBuilder >  m_faceBuilder;

//   /// The volume integrator
//   Framework::VolumeIntegrator m_volumeIntegrator;
//
//   /// String for configuring the numerical integrator QuadratureType
//   std::string m_intquadStr;
// 
//   /// String for configuring the numerical integrator Order
//   std::string m_intorderStr;
  
  /// Interface flux computation strategy
  Common::SelfRegistPtr< BaseInterfaceFlux > m_interfaceflux;

  /// String to configure interface flux computation strategy
  std::string m_interfacefluxStr;
  
  /// vector containing the  FluxReconstructionElementData for different element types
  std::vector< FluxReconstructionElementData* > m_frLocalData;
  
  /// pointer to states reconstructor strategy
  Common::SelfRegistPtr< ReconstructStatesFluxReconstruction > m_statesReconstructor;
  
  /// Flux point distribution
  Common::SelfRegistPtr< BasePointDistribution > m_fluxpntdistribution;

  /// String to configure flux point distribution
  std::string m_fluxpntdistributionStr;
  
  /// Solution point distribution
  Common::SelfRegistPtr< BasePointDistribution > m_solpntdistribution;

  /// String to configure flux point distribution
  std::string m_solpntdistributionStr;
  
  /// The boundary condition state computer strategies
  std::vector< Common::SelfRegistPtr< BCStateComputer > > m_bcs;

  /// The boundary condition state computer strategies, as SafePtrs
  std::vector< Common::SafePtr< BCStateComputer > > m_bcsSP;

  /// The boundary condition strategy types
  std::vector< std::string > m_bcTypeStr;

  /// The boundary condition strategy names for configuration
  std::vector< std::string > m_bcNameStr;

  /// The boundary condition TRS names
  std::vector< std::vector< std::string > > m_bcTRSNameStr;
  
  /// variable for maximum number of points in which the Riemann solver is evaluated
  CFuint m_maxNbrRFluxPnts;
  
  /// variable for maximum number of statesData that has to be computed
  CFuint m_maxNbrStatesData;
  
  /// factor to multiply the residual with, coming from the time discretization
  CFreal m_resFactor;
  
  /// map between the boundary TRS and the start index of faces with a certain orientation
  std::map< std::string , std::vector< std::vector< CFuint > > > m_bndFacesStartIdxs;
  
  /// start index of inner faces with a certain orientation
  std::vector< CFuint > m_innerFacesStartIdxs;
  
  /// String for the boundary face terms computer
  std::string m_bndFaceTermComputerStr;

  /// pointer to boundary face term computer
  Common::SelfRegistPtr< BaseBndFaceTermComputer > m_bndFaceTermComputer;
  
//   /// socket for solution coordinates in 1D
//   Framework::DataSocketSource< std::vector< CFreal > > socket_solCoords1D;
//   
//   /// socket for flux coordinates in 1D
//   Framework::DataSocketSource< std::vector< CFreal > > socket_flxCoords1D;

};  // end of class FluxReconstructionSolverData

//////////////////////////////////////////////////////////////////////////////

/// Definition of a MethodCommand for FluxReconstructionMethod
typedef Framework::MethodCommand< FluxReconstructionSolverData > FluxReconstructionSolverCom;

/// Definition of a command provider for FluxReconstructionMethod
typedef FluxReconstructionSolverCom::PROVIDER FluxReconstructionSolverComProvider;

/// Definition of a MethodStrategy for FluxReconstructionMethod
typedef Framework::MethodStrategy< FluxReconstructionSolverData > FluxReconstructionSolverStrategy;

//////////////////////////////////////////////////////////////////////////////

  } // namespace FluxReconstructionMethod
} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Numerics_FluxReconstructionMethod_FluxReconstructionSolverData_hh

