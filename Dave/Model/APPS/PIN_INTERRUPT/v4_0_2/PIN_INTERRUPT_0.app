<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="PIN_INTERRUPT" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0" description="The PIN_INTERRUPT APP invokes user interrupt handler in a response &#xA;to rising and/or falling edge event signal on a pin." mode="NOTSHARABLE" version="4.0.2" minDaveVersion="4.0.0" instanceLabel="PIN_INTERRUPT_ANG_MAX" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="signal_a_b" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_input_A_B" hwResource="//@hwResources.2" visible="true" solverVariableName="sv0" solverVariableValue="b"/>
  <virtualSignals name="external_event_pin" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iopad" hwSignal="pad" hwResource="//@hwResources.1"/>
  <virtualSignals name="trigger_out" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_TriggerPulse" hwSignal="tr" hwResource="//@hwResources.2"/>
  <virtualSignals name="trigger_in" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_trin" hwSignal="trin" hwResource="//@hwResources.3"/>
  <virtualSignals name="iout" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iout" hwSignal="iout" hwResource="//@hwResources.3"/>
  <virtualSignals name="sr_node" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_signal" hwSignal="signal_in" hwResource="//@hwResources.0"/>
  <virtualSignals name="Pin_signal" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/__pin_vs_pin_interrupt_iopad" hwSignal="pin" hwResource="//@hwResources.4"/>
  <requiredApps URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/appres_cpu" requiredAppName="CPU_CTRL_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CPU_CTRL_XMC1/v4_0_8/CPU_CTRL_XMC1_0.app#/"/>
  </requiredApps>
  <hwResources name="External Event" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/hwres_interrupt" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/cpu/cpu_0.dd#//@provided.36"/>
  </hwResources>
  <hwResources name="Pin" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/hwres_port_pin" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/port2/port2_2.dd#//@provided.40"/>
  </hwResources>
  <hwResources name="ers_etl" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/hwres_eru_ers_etl" resourceGroupUri="peripheral/eru/*/ers_etl/*" mResGrpUri="peripheral/eru/*/ers_etl/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/eru0/eru0_0.dd#//@provided.14"/>
  </hwResources>
  <hwResources name="ogu" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/hwres_eru_ogu" resourceGroupUri="peripheral/eru/*/ogu/*" mResGrpUri="peripheral/eru/*/ogu/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/eru0/eru0_0.dd#//@provided.7"/>
  </hwResources>
  <hwResources name="Pin" URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/__pin_hwres_port_pin" resourceGroupUri="devicepackage/0/9" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.29"/>
  </hwResources>
  <connections URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iopad/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_input_A_B" systemDefined="true" sourceSignal="external_event_pin" targetSignal="signal_a_b" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_TriggerPulse/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_trin" systemDefined="true" sourceSignal="trigger_out" targetSignal="trigger_in" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iout/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_signal" systemDefined="true" sourceSignal="iout" targetSignal="sr_node" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.5"/>
  <connections URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iopad/http://resources/4.0.2/app/PIN_INTERRUPT/0/__pin_vs_pin_interrupt_iopad" systemDefined="true" sourceSignal="external_event_pin" targetSignal="Pin_signal" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.6"/>
  <connections URI="http://resources/4.0.2/app/PIN_INTERRUPT/0/http://resources/4.0.2/app/PIN_INTERRUPT/0/__pin_vs_pin_interrupt_iopad/http://resources/4.0.2/app/PIN_INTERRUPT/0/vs_pin_interrupt_iopad" systemDefined="true" sourceSignal="Pin_signal" targetSignal="external_event_pin" srcVirtualSignal="//@virtualSignals.6" targetVirtualSignal="//@virtualSignals.1"/>
</ResourceModel:App>
