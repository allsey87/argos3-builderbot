/**
 * @file <argos3/plugins/robots/pi-puck/simulator/pipuck_rangefinders_default_sensor.h>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#ifndef PIPUCK_RANGEFINDERS_DEFAULT_SENSOR_H
#define PIPUCK_RANGEFINDERS_DEFAULT_SENSOR_H

namespace argos {
   class CPiPuckRangefindersDefaultSensor;
   class CControllableEntity;
   class CEmbodiedEntity;
   struct SAnchor;
}

#include <argos3/core/simulator/sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_rangefinders_sensor.h>

namespace argos {

   class CPiPuckRangefindersDefaultSensor : public CSimulatedSensor,
                                            public CCI_PiPuckRangefindersSensor {

   public:

      struct SSimulatedInterface : SInterface {
         /* constructor */
         SSimulatedInterface(const std::string& str_label,
                             const SAnchor& s_anchor,
                             Real f_range);
         /* members */
         const SAnchor& Anchor;
         Real Range;
      };

      CPiPuckRangefindersDefaultSensor();

      virtual ~CPiPuckRangefindersDefaultSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:
      Real ConvertToMeters(Real f_raw) {
         static const Real fConversionFactor = Real(1.0);
         return (f_raw * fConversionFactor);
      }

      Real ConvertToLux(Real f_raw) {
         static const Real fConversionFactor = Real(1.0);
         return (f_raw * fConversionFactor);
      }

   private:
      CEmbodiedEntity* m_pcEmbodiedEntity;
      CControllableEntity* m_pcControllableEntity;

      bool m_bShowRays;

      std::vector<SSimulatedInterface> m_vecSimulatedInterfaces;

   };
}

#endif