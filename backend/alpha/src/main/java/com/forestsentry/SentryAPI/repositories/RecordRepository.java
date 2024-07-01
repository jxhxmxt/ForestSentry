package com.forestsentry.SentryAPI.repositories;

import java.util.UUID;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

import com.forestsentry.SentryAPI.models.entities.Record;

public interface RecordRepository extends JpaRepository<Record, UUID> {
    public Record findFirstByOrderByTimestampDesc();
    public Record findFirstByDeviceID(String deviceId);
    public Page<Record> findAllByDeviceIDOrderByTimestampAsc(String deviceId, Pageable pageable);
}
