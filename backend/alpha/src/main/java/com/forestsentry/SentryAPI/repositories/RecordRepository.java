package com.forestsentry.SentryAPI.repositories;

import java.util.UUID;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

import com.forestsentry.SentryAPI.models.entities.Record;

public interface RecordRepository extends JpaRepository<Record, UUID> {
    public Record findFirstRecordOrderByTimestampAsc();
    public Record findFirstRecordByDeviceIdOrderByTimestampAsc(String deviceId);
    public Page<Record> findAllByDeviceId(Pageable pageable);
}